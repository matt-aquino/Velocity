#pragma once
#include "glm/glm.hpp"
#include "Velocity/Core/Components/CoreComponents.h"
#include "entt.hpp"

namespace Velocity
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top); // defines camera bounds
		~OrthographicCamera();

		void SetPosition(const glm::vec3& position);
		void SetRotation(float rotation);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjMatrix; }

	private:
		void RecalculateViewMatrix();


		glm::mat4 m_ProjMatrix, m_ViewMatrix, m_ViewProjMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};


	class PerspectiveCamera
	{
	public:

		enum class CameraDirection
		{
			FORWARD = 0, BACKWARD,
			LEFT, RIGHT,
			UP, DOWN,
		};

		PerspectiveCamera(TransformComponent& transform);
		PerspectiveCamera(const glm::vec3& position);
		~PerspectiveCamera();

		// mutators
		void MoveCamera(CameraDirection direction, float deltaTime);
		void SetCameraSpeed(float speed);
		void SetCameraFOV(float fov);
		void AddCameraPitch(float pitch);
		void AddCameraYaw(float yaw);
		void SetAspectRatio(uint32_t width, uint32_t height);

		// accessors
		inline const glm::vec3 GetPosition() { return m_Transform.GetPosition(); }
		inline const float GetYaw() { return m_Yaw; }
		inline const float GetPitch() { return m_Pitch; }
		inline const float GetCameraSpeed() { return m_Speed; }
		inline const float GetFOV() { return m_FOV; }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjMatrix; }

	private:
		void RecalculateViewMatrix();
		void SetPosition(const glm::vec3& position);

		glm::mat4 m_ProjMatrix, m_ViewMatrix, m_ViewProjMatrix;
		float m_Pitch = 0.0f, m_Yaw = -90.0f;
		float m_Speed = 1.0f;
		float m_FOV = 45.0f;
		float m_AspectRatio = 0.0f;

		TransformComponent m_Transform;

		glm::vec3 WorldUp	= glm::vec3(0.0f, 1.0f, 0.0f);
		
		glm::vec3 Up	= glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
	};
}