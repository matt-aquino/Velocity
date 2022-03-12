#pragma once
#include "Scene.h"
#include "Velocity/Core/Components/CoreComponents.h"

namespace Velocity
{
	class GameObject
	{
	public:
		GameObject(std::string& name, entt::entity handle, Scene* scene)
			: m_Name(name), m_EntityHandle(handle), m_Scene(scene) {}

		GameObject(const GameObject& other) = default;

		void SetName(std::string& newName) { m_Name = newName; }

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			VL_CORE_ASSERT(!HasComponent<T>(), "Entity doesn't have component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			VL_CORE_ASSERT(!HasComponent<T>(), "Entity doesn't have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			VL_CORE_ASSERT(!HasComponent<T>(), "Entity doesn't have component!");
			return m_Scene->m_Registry.get<T&>(m_EntityHandle);
		}


		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

	private:
		std::string m_Name;
		entt::entity m_EntityHandle;
		Scene* m_Scene;

		// default components
		TransformComponent m_TransformComponent;
		TagComponent m_TagComponent;
	};
}