#pragma once

#include "Evil.h"
#include "Level.h"

#include <imgui/imgui.h>

class GameLayer : public Evil::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Evil::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Evil::Event& e) override;
	bool OnMouseButtonPressed(Evil::MouseButtonPressedEvent& e);
	bool OnWindowResize(Evil::WindowResizeEvent& e);
private:
	void ResizeCamera(uint32_t width, uint32_t height);
private:
	Evil::Scope<Evil::OrthographicCamera> m_Camera;

	Level m_Level;
	ImFont* m_Font;

	float m_TextSizeDiff = 0.0f;
	int m_DiffDirection = -1;

	float m_CameraSize = 9.0f;

	enum class GameState
	{
		MainMenu = 0,
		Play = 1,
		GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};
