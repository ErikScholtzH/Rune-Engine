#include "rune_pch.h"

#include "Camera.h"

namespace Rune {

	Camera::Camera() : m_Type(CameraType::Perspective) { // TODO provide defaults values
		m_Position = glm::vec3(1.0f, 0.0f, 2.0f);
		glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Direction = glm::normalize(m_Position - target);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Right = glm::normalize(glm::cross(up, m_Direction));
		m_Up = glm::normalize(glm::cross(m_Direction, m_Right));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
		RecalculateViewMarix();
	}

	Camera::Camera(CameraType type, glm::vec3 position) { // TODO provide defaults values
		m_Position = position;
		glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Direction = glm::normalize(m_Position - target);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Right = glm::normalize(glm::cross(up, m_Direction));
		m_Up = glm::normalize(glm::cross(m_Direction, m_Right));

		m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f); 

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
		switch (type) {
		case CameraType::Ortholinear: {
			float OrthoSize = 10.0f;
			float OrthoLeft = -OrthoSize * m_AspectRatio;
			float OrthoRight = OrthoSize * m_AspectRatio;
			float OrthoBottom = -OrthoSize;
			float OrthoTop = OrthoSize;
			m_ProjectionMatrix = glm::ortho(OrthoLeft, OrthoRight, OrthoBottom, OrthoTop, m_NearPlane, m_FarPlane);
			break;
		}	
		case CameraType::Perspective: {
			m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
			break;
		}
		default: {
			RUNE_CORE_ASSERT(false, "Unknown camera type");
			break;
		}
		};
		RecalculateViewMarix();
	}

	Camera::~Camera() {

	}

	void Camera::RecalculateViewMarix() {
		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

		glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX; // Apply in ZYX order (common for cameras)
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * rotationMatrix;

		m_RotationMatrix = rotationMatrix;
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}

