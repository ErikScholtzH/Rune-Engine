#include "rune_pch.h"
#include "CameraController.h"

#include "Rune/Input.h"
#include "Rune/KeyCodes.h"

namespace Rune {
	CameraController::CameraController() {
		m_Camera = Camera::Camera();
		m_AspectRatio = 16.0f / 9.0f;
	}
	CameraController::CameraController(float aspectRatio, Camera::CameraType type, glm::vec3 position)
		: m_AspectRatio(aspectRatio), m_Camera(type, position)
	{
	}

	void CameraController::OnUpdate(Timestep timestep)
	{
		if (Rune::Input::IsKeyPressed(RUNE_KEY_A)) {
			m_CameraPosition.x -= GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_D)) {
			m_CameraPosition.x += GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_SPACE)) {
			m_CameraPosition.y += GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_LEFT_CONTROL)) {
			m_CameraPosition.y -= GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_W)) {
			m_CameraPosition.z -= GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_S)) {
			m_CameraPosition.z += GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_UP)) {
			m_CameraRotation.x += GetCameraRotationSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_DOWN)) {
			m_CameraRotation.x -= GetCameraRotationSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_LEFT)) {
			m_CameraRotation.y += GetCameraRotationSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_RIGHT)) {
			m_CameraRotation.y -= GetCameraRotationSpeed() * timestep;
		}

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);
	}

	void CameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(RUNE_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(RUNE_BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		m_ZoomLevel = - 3.0f * e.GetYOffset();
		m_Camera.SetFov(m_ZoomLevel);
		m_Camera.SetProjection(m_Camera.GetFov(), m_Camera.GetAspectRatio(), m_Camera.GetNearPlane(), m_Camera.GetFarPlane());
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e) {
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetAspectRatio(m_AspectRatio);
		m_Camera.SetProjection(m_Camera.GetFov(), m_Camera.GetAspectRatio(), m_Camera.GetNearPlane(), m_Camera.GetFarPlane());
		return false;
	}

}