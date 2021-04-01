#pragma once

#include "Evil/Core/Base.h"

#include "Evil/Core/Window.h"
#include "Evil/Core/LayerStack.h"
#include "Evil/Events/Event.h"
#include "Evil/Events/ApplicationEvent.h"

#include "Evil/Core/Timestep.h"

#include "Evil/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Evil
{
	class  Application
	{
	public:
		Application(const std::string& name = "Evill App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* Overlay);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;

		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


