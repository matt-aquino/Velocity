#pragma once 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_access.hpp"

#include <string>

namespace Velocity
{
	struct TagComponent
	{
		TagComponent() : m_Tag("") {}
		TagComponent(const std::string& tag) : m_Tag(tag) {}

		void SetTag(const std::string& tag) { m_Tag = tag; }
		const std::string& GetTag() { return m_Tag; }

		std::string m_Tag;
	};

	struct TransformComponent
	{
		TransformComponent() { m_Transform = glm::mat4(1.0f); }
		TransformComponent(glm::mat4& transform) : m_Transform(transform) {}
		TransformComponent(const TransformComponent&) = default;

		TransformComponent(glm::vec3& position)
		{
			m_Transform = glm::translate(glm::mat4(1.0f), position);		
		}

		// accessors
		glm::vec3 GetPosition() { return glm::vec3(m_Transform[3]); } // translation is the last column in the matrix
		glm::vec3 GetRotation() { return glm::vec3(glm::column(m_Transform, 1)); }
		glm::vec3 GetScale()	 
		{ 
			glm::vec3 scale = glm::vec3(m_Transform[0][0], m_Transform[1][1], m_Transform[2][2]); // scale sits on the diagonal of the matrix
			return scale; 
		}

		// mutators
		void SetPosition(const glm::vec3& position) { m_Transform[3] = glm::vec4(position, 1.0f); }
		void SetRotation(const glm::vec3& rotation, float angle) { m_Transform = glm::rotate(m_Transform, angle, rotation); }
		void SetScale(const glm::vec3& scale) { m_Transform = glm::scale(m_Transform, scale); }
		//void SetScale(const glm::vec3& scale) { m_Transform = glm::scale(glm::mat4(1.0f), scale); }

		// overload operators to use perform math on the TransformComponent itself
		operator glm::mat4& () { return m_Transform; }
		operator const glm::mat4& () const { return m_Transform; }

		glm::mat4 m_Transform;
	};

	struct ScriptComponent
	{
	};

	struct ColliderComponent
	{
		virtual void UpdateTransform() = 0;

		TransformComponent m_Transform;
	};
}