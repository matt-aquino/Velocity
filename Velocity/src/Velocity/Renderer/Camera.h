#pragma once
#include "glm/glm.hpp"

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

	};

}