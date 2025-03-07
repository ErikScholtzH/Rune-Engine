#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace Rune {
	class Camera {
	public:
		enum class CameraType {
			Ortholinear = 0, 
			Perspective = 1
		};

		Camera();
		Camera(CameraType type, glm::vec3 position);
		~Camera();
		
		const inline CameraType GetType() const{ return m_Type; }
		
		const glm::vec3& GetPosition() { return m_Position;  }
		const glm::vec3& GetDirection() { return m_Direction; }
		const glm::vec3& GetUpVector() { return m_Up; }
		const glm::vec3& getRotation() { return m_Rotation; }

		void SetPosition(glm::vec3 position) { m_Position = position; RecalculateViewMarix(); }
		void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; RecalculateViewMarix(); }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
		const glm::mat4& GetRotationMatrix() { return m_RotationMatrix; }

		const glm::mat4& GetTransformRotation();

		const inline float GetNear() const { return m_NearPlane; }
		const inline float GetFar() const { return m_FarPlane; }

	private:
		void RecalculateViewMarix();

		CameraType m_Type;

		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_Rotation;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::mat4 m_RotationMatrix;


		float m_AspectRatio = 16.0f / 9.0f;
		float m_Fov = 90.0f;
		float m_Exposure = 1.0f;
		float m_Gamma = 2.0f;
		float m_Speed = 1.0f;

		float m_NearPlane = 0.001f;
		float m_FarPlane = 400.0f;

	};
}