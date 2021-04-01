#pragma once

#include "Evil/Renderer/OrthographicCamera.h"
#include "Evil/Core/Timestep.h"

#include "Evil/Events/ApplicationEvent.h"
#include "Evil/Events/MouseEvent.h"

namespace Evil
{
	struct OrthographicCameraBouns
	{
		float Left, Right;
		float Buttom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Buttom; }
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		~OrthographicCameraController() = default;

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel(float level) const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }

		const OrthographicCameraBouns& GetBounds() const { return m_Bounds; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		void CalculateView();

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBouns m_Bounds;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}