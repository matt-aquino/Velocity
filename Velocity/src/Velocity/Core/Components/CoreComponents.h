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
		TransformComponent(glm::mat4& transform) : m_Transform(transform) {}

		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::vec3& position = glm::vec3(0.0f), glm::vec3& eulerRotation = glm::vec3(0.0f), glm::vec3& scale = glm::vec3(1.0f))
		{
			m_Transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 0.0f, eulerRotation) * glm::scale(glm::mat4(1.0f), scale); // TRS transformation
		}

		// accessors
		glm::vec3 GetPosition() { return glm::vec3(glm::column(m_Transform, 0)); }
		glm::vec3 GetRotation() { return glm::vec3(glm::column(m_Transform, 1)); }
		glm::vec3 GetScale()	 { return glm::vec3(glm::column(m_Transform, 2)); }

		// mutators
		void SetPosition(const glm::vec3& position) { m_Transform[0] = glm::vec4(position, 1.0f); }
		void SetRotation(const glm::vec3& rotation) { m_Transform[1] = glm::vec4(rotation, 1.0f); }
		void SetScale(const glm::vec3& scale)		{ m_Transform[2] = glm::vec4(scale,	   1.0f); }

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