#pragma once
#include "Scene.h"
#include "Velocity/Core/Components/CoreComponents.h"

namespace Velocity
{
	class GameObject
	{
	public:
		GameObject(std::string& name, Scene* scene)
			: m_Name(name), m_Scene(scene)
		{
			m_EntityHandle = m_Scene->GetRegistry().create();
			//AddComponent<TransformComponent>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
			AddComponent<TransformComponent>(glm::mat4(1.0f));
			AddComponent<TagComponent>("Object");
		}

		//GameObject(const GameObject& other) = default;

		void SetName(std::string& newName) { m_Name = newName; }

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			VL_CORE_ASSERT(!HasComponent<T>(), "Entity doesn't have component!");
			return m_Scene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			VL_CORE_ASSERT(!HasComponent<T>(), "Entity doesn't have component!");
			m_Scene->GetRegistry().remove<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			VL_CORE_ASSERT(!HasComponent<T>(), "Entity doesn't have component!");
			return m_Scene->GetRegistry().get<T&>(m_EntityHandle);
		}


		template<typename T>
		bool HasComponent()
		{
			return m_Scene->GetRegistry().all_of<T>(m_EntityHandle);
		}

	private:
		std::string m_Name;
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene;
	};
}