#include "vlpch.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

#define IDENTITY_MATRIX glm::mat4(1.0f)

namespace Velocity
{
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

	// ORTHOGRAPHIC CAMERA
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



	// PERSPECTIVE CAMERA
}