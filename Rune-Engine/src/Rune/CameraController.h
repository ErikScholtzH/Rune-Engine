#pragma once

#include "Rune/Renderer/Camera.h"
#include "Rune/Core/Timestep.h"

#include "Rune/Core/Events/ApplicationEvent.h"
#include "Rune/Core/Events/MouseEvent.h"

namespace Rune {

	class CameraController {
	public:
		CameraController();
		CameraController(float aspectRatio, Camera::CameraType type, glm::vec3 position);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		const inline float GetCameraSpeed() const { return m_CameraSpeed; }
		const inline float GetCameraRotationSpeed() const { return m_CameraRotationSpeed; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		Camera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 2.0f };
		glm::vec3 m_CameraRotation = { 0.0f, 0.0f, 0.0f };

		float m_Exposure = 1.0f;
		float m_Gamma = 2.0f;
		float m_CameraSpeed = 5.0f;
		float m_CameraRotationSpeed = 90.0f;
	};

}