#include "vlpch.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

#define IDENTITY_MATRIX glm::mat4(1.0f)

namespace Velocity
{
	// =================  ORTHOGRAPHIC CAMERA  =================

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)) 
	{
		m_Position = glm::vec3(0.0f);
		m_Rotation = 0.0f;
		m_ViewMatrix = IDENTITY_MATRIX;
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(IDENTITY_MATRIX, m_Position) * glm::rotate(IDENTITY_MATRIX, glm::radians(m_Rotation), Z_AXIS);
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}
	
	// =================  PERSPECTIVE CAMERA  =================

	PerspectiveCamera::PerspectiveCamera(TransformComponent& transform)
	{
		m_Transform = transform;
		m_ProjMatrix = glm::perspective(45.0f, 16.0f / 9.0f, 0.01f, 1000.0f);
		m_ViewMatrix = glm::lookAt(m_Transform.GetPosition(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	PerspectiveCamera::PerspectiveCamera(glm::vec3& position)
	{
		m_Transform = { position };
		auto&[x, y] = Renderer::GetWindowSize();
		m_AspectRatio = (float)x / (float)y;
		m_ProjMatrix = glm::perspective(45.0f, m_AspectRatio, 0.01f, 1000.0f);
		RecalculateViewMatrix();
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	void PerspectiveCamera::MoveCamera(CameraDirection direction, float deltaTime)
	{
		glm::vec3 moveDirection;
		switch (direction)
		{
		case CameraDirection::FORWARD:
			moveDirection = Front;
			break;

		case CameraDirection::BACKWARD:
			moveDirection = -Front;
			break;

		case CameraDirection::LEFT:
			moveDirection = -Right;
			break;

		case CameraDirection::RIGHT:
			moveDirection = Right;
			break;

		case CameraDirection::UP:
			moveDirection = Up;
			break;

		case CameraDirection::DOWN:
			moveDirection = -Up;
			break;
		}

		glm::vec3 position = GetPosition();
		position += moveDirection * m_Speed * deltaTime;
		SetPosition(position);
	}

	void PerspectiveCamera::SetCameraSpeed(float speed)
	{
		m_Speed = speed;
	}
	
	void PerspectiveCamera::SetCameraFOV(float fov)
	{
		m_FOV = fov;
		m_ProjMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.01f, 1000.0f);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Transform.SetPosition(position);
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::AddCameraPitch(float pitch)
	{
		m_Pitch -= pitch;

		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;

		RecalculateViewMatrix();
	}

	void PerspectiveCamera::AddCameraYaw(float yaw)
	{
		m_Yaw = glm::mod(m_Yaw + yaw, 360.0f); // keep values bound between 0 and 360 degrees
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetAspectRatio(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		m_ProjMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.01f, 1000.0f);
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::vec3 direction;
		direction.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		direction.y = glm::sin(glm::radians(m_Pitch));
		direction.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));

		Front = glm::normalize(direction);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));

		glm::vec3 position = m_Transform.GetPosition();
		m_ViewMatrix = glm::lookAt(position, position + Front, Up);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}
}