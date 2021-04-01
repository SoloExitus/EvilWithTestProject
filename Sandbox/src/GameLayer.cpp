#include "GameLayer.h"
#include <imgui/imgui.h>

#include "Random.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer()
	:Layer("MiniGame")
{
	Evil::Window& window = Evil::Application::Get().GetWindow();
	float windowWidth = window.GetWidth();
	float windowHeight = window.GetHeight();
	float aspectRatio = windowWidth / windowHeight;
	float bottom = -m_CameraSize;
	float top = m_CameraSize;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = Evil::CreateScope<Evil::OrthographicCamera>(left, right, bottom, top);

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Evil::Timestep ts)
{
	if (m_TextSizeDiff >= 60.0f)
	{
		m_DiffDirection = -1;
	}
	else if (m_TextSizeDiff <= 0)
	{
		m_DiffDirection = 1;
	}

	m_TextSizeDiff += m_DiffDirection * 40.0f * ts;

	m_TextSizeDiff = std::clamp(m_TextSizeDiff, 0.0f, 60.0f);

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ 0, playerPos.y, 0.0f });

	m_Level.GetPlayer().UpdateParticles(ts);

	switch (m_State)
	{
		case GameState::Play:
		{
			m_Level.OnUpdate(ts);
			break;
		}
	}

	// Render
	Evil::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Evil::RenderCommand::Clear();

	Evil::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Evil::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	ImVec2& windowPos = ImGui::GetWindowPos();
	Evil::Window& window = Evil::Application::Get().GetWindow();
	int windowWidth = window.GetWidth();
	int windowHeight = window.GetHeight();

	uint32_t playerScore = m_Level.GetScore();
	std::string scoreStr = std::string("Your Score: ") + std::to_string(playerScore);

	switch (m_State)
	{
		case GameState::Play:
		{
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f - m_TextSizeDiff, { windowPos.x + windowWidth * 0.5f - 300.0f + m_TextSizeDiff * 2, windowPos.y + 50.0f + m_TextSizeDiff / 2 }, 0xffffffff, "Click to Play!");
			break;
		}
		case GameState::GameOver:
		{
			windowPos.x += windowWidth * 0.5f - 330.0f;
			windowPos.y += 50.0f;

			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f - m_TextSizeDiff, { windowPos.x + m_TextSizeDiff * 2, windowPos.y + m_TextSizeDiff / 2 }, 0xffffffff, "Click to Restart!");

			windowPos.x += 150.0f;
			windowPos.y += 100.0f;
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, windowPos, 0xffffffff, scoreStr.c_str());
			break;
		}
	}
}

void GameLayer::OnEvent(Evil::Event& e)
{
	Evil::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Evil::WindowResizeEvent>(EVIL_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<Evil::MouseButtonPressedEvent>(EVIL_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Evil::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Evil::WindowResizeEvent& e)
{
	ResizeCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::ResizeCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;
	float bottom = -m_CameraSize;
	float top = m_CameraSize;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera->SetProjection(left, right, bottom, top);
}
