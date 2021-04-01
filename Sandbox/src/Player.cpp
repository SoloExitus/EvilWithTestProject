#include "Player.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

Player::Player()
	:m_ParticleSystem(m_MaxParticles)
{
	m_SmokeParticle.Position = { 0.0f, 0.0f, 0.0f };
	m_SmokeParticle.Velocity = { -3.0f, 0.0f }, m_SmokeParticle.VelocityVariation = { 1.0f, 2.0f };
	m_SmokeParticle.SizeBegin = 0.25f, m_SmokeParticle.SizeEnd = 0.0f, m_SmokeParticle.SizeVariation = 0.15f;
	m_SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	m_SmokeParticle.LifeTime = 4.0f;

	m_EngineParticle.Position = { 0.0f, 0.0f, 0.0f };
	m_EngineParticle.Velocity = { -4.0f, 0.0f }, m_EngineParticle.VelocityVariation = { 2.0f, 1.0f };
	m_EngineParticle.SizeBegin = 0.35f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
	m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
	m_EngineParticle.LifeTime = 1.0f;

	CalculateTransform();
}

void Player::LoadAssets()
{
	m_SpaceShipSprite = Evil::Texture2D::Create("assets/textures/SpaceShip.png");
}

void Player::OnUpdate(Evil::Timestep ts)
{
	m_Time += ts;

	glm::vec2 emissionPoint = { 0.0f, -0.6f };
	float rotation = GetRotation();
	glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);

	if (ActiveEngine())
	{
		m_VelocityY += m_EnginePower;

		m_EngineParticle.Position = glm::vec3{ m_Position.x - 0.1f,m_Position.y, 1.0f } + glm::vec3(rotated.x, rotated.y, 0.0f );
		m_EngineParticle.Velocity.y = -m_VelocityY * 0.3f - 0.2f;
		m_ParticleSystem.Emit(m_EngineParticle);
	}
	else
	{
		m_VelocityY -= m_Gravity;
	}

	m_VelocityY = glm::clamp(m_VelocityY, -20.0f, 20.0f);
	m_Position.y += m_VelocityY * (float)ts;

	CalculateTransform();

	// Particles
	if (m_Time > m_SmokeEmitInterval)
	{
		m_SmokeParticle.Position = glm::vec3(m_Position.x - 0.1f ,m_Position.y, 0.1f) +  glm::vec3(rotated.x, rotated.y, 0.0f );
		m_ParticleSystem.Emit(m_SmokeParticle);
		m_Time -= m_SmokeEmitInterval;
	}
}

void Player::OnRender()
{
	m_ParticleSystem.OnRender();
	Evil::Renderer2D::DrawQuad(m_Trasform, m_SpaceShipSprite);
}

void Player::Reset()
{
	m_Position = { 0.0f, 0.0f };
	m_VelocityY = 0.0f;

	CalculateTransform();
}

void Player::CalculateTransform()
{
	m_Trasform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0.2f })
		* glm::rotate(glm::mat4(1.0f), GetRotation(), { 0.0f, 0.0f , 1.0f })
		* glm::scale(glm::mat4(1.0f), { 1.0f, 1.3f , 1.0f });
}

bool Player::ActiveEngine() const
{
	return Evil::Input::IsKeyPressed(Evil::Key::Space) || Evil::Input::IsKeyPressed(Evil::Key::W) || Evil::Input::IsKeyPressed(Evil::Key::Up);
}
