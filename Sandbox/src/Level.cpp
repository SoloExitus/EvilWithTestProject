#include "Level.h"

#include <glm/gtc/matrix_transform.hpp>

static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
	int H = (int)(hsv.x * 360.0f);
	double S = hsv.y;
	double V = hsv.z;

	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
}

void Level::Init()
{
	m_PillarTexture = Evil::Texture2D::Create("assets/textures/Triangle.png");
	m_Player.LoadAssets();
	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		SetRandomPillar(m_Pillars[i], i * 10.0f + 20.0f);
}

void Level::OnUpdate(Evil::Timestep ts)
{
	m_Player.OnUpdate(ts);

	m_Player.UpdateParticles(ts);

	if (CollisionTest())
	{
		m_GameOver = true;
		return;
	}

	for (Pillar& pillar : m_Pillars)
	{
		if (pillar.PositionX < m_DestroyPoint)
		{
			SetRandomPillar(pillar, m_CreatePoint);
		}
		else
		{
			pillar.PositionX -= 5.0f * ts;
			//pillar.TopPositionY -= 0.3f * ts;
			//pillar.BottomPositionY += 0.3f * ts;
		}

		if (pillar.PositionX < 0.0f && pillar.New)
		{
			pillar.New = false;
			m_Score++;
		}
	}

	m_PillarHSV.x += 0.1f * ts;
	if (m_PillarHSV.x > 1.0f)
		m_PillarHSV.x = 0.0f;

}

void Level::OnRender()
{
	// Background
	Evil::Renderer2D::DrawQuad(glm::vec3(0.0f), { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

	glm::vec4 color = HSVtoRGB(m_PillarHSV);

	// Floor and ceiling
	Evil::Renderer2D::DrawQuad({ 0.0f,  34.0f }, { 50.0f, 50.0f }, color);
	Evil::Renderer2D::DrawQuad({ 0.0f, -34.0f }, { 50.0f, 50.0f }, color);

	for (auto& pillar : m_Pillars)
	{
		Evil::Renderer2D::DrawRotatedQuad({ pillar.PositionX, pillar.TopPositionY}, pillar.Scale, glm::radians(180.0f), m_PillarTexture, 1.0f,color);
		Evil::Renderer2D::DrawQuad({ pillar.PositionX, pillar.BottomPositionY}, pillar.Scale, m_PillarTexture, 1.0f, color);
	}

	m_Player.OnRender();
}

void Level::Reset()
{
	m_GameOver = false;

	m_Player.Reset();
	m_Score = 0;

	for (int i = 0; i < 5; i++)
		SetRandomPillar(m_Pillars[i], i * 10.0f + 20.0f);
}

void Level::SetRandomPillar(Pillar& pillar, float position)
{
	pillar.PositionX = position;
	pillar.New = true;

	float center = Random::Float() * 35.0f - 17.5f;
	float gap = 2.0f + Random::Float() * 3.0f;

	pillar.TopPositionY = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
	pillar.BottomPositionY = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
}

static bool PointInTri(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
{
	float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}

bool Level::CollisionTest()
{
	const glm::vec2 playerPos = m_Player.GetPosition();

	if (glm::abs(playerPos.y) > 8.5f)
		return true;

	const glm::mat4& playerTrasform = m_Player.GetTransform();

	glm::vec4 playerTransformedVerts[4];
	for (int i = 0; i < 4; i++)
	{
		playerTransformedVerts[i] = playerTrasform * m_PlayerVertices[i];
	}

	// To match Triangle.png (each corner is 10% from the texture edge)
	glm::vec4 pillarVertices[3] = {
		{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
	};

	for (auto& p : m_Pillars)
	{
		glm::vec2 tri[3];

		// Top pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), { p.PositionX, p.TopPositionY, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { p.Scale.x, p.Scale.y, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

		// Bottom pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), { p.PositionX, p.BottomPositionY, 0.0f })
				* glm::scale(glm::mat4(1.0f), { p.Scale.x, p.Scale.y, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

	}

	return false;
}
