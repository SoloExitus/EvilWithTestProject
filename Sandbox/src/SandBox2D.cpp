#include "SandBox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandBox2D::SandBox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{

}

void SandBox2D::OnAttach()
{
	EVIL_PROFILE_FUNCTION();

	m_CheckerboardTexture = Evil::Texture2D::Create("assets/textures/Checkerboard.png");
	m_CLogo = Evil::Texture2D::Create("assets/textures/C++LOGO.png");

	m_SpriteSheet = Evil::Texture2D::Create("assets/textures/RPGsheet.png");
	m_TextureTree = Evil::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
}

void SandBox2D::OnDetach()
{
	EVIL_PROFILE_FUNCTION();
}

void SandBox2D::OnUpdate(Evil::Timestep ts)
{
	EVIL_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Evil::Renderer2D::ResetStats();
	{
		EVIL_PROFILE_SCOPE("Renderer Prep");

		Evil::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
		Evil::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		EVIL_PROFILE_SCOPE("Renderer Draw");
		Evil::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Evil::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);

		Evil::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Evil::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Evil::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);

		Evil::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);

		Evil::Renderer2D::DrawQuad({ 0.0f, -3.0f, 0.1f }, { 1.0f, 1.0f }, m_CLogo);
		Evil::Renderer2D::DrawRotatedQuad({ -1.0f, -3.0f, 0.1f }, { 1.0f, 2.0f }, glm::radians(rotation), m_TextureTree);

		Evil::Renderer2D::EndScene();

		/*Evil::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Evil::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Evil::Renderer2D::EndScene();*/
	}

}

void SandBox2D::OnImGuiRender()
{
	EVIL_PROFILE_FUNCTION();
		
	ImGui::Begin("Settings");

	auto stats = Evil::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
	
}

void SandBox2D::OnEvent(Evil::Event& e)
{
	m_CameraController.OnEvent(e);
}
