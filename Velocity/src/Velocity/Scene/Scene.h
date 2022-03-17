#pragma once

#include "entt.hpp"
#include <string>

namespace Velocity
{
	class GameObject;

	class Scene
	{
	public:
		Scene();

		~Scene();

		GameObject* CreateGameObject(const std::string& name);
		void OnUpdate(float deltaTime);

		inline entt::registry& GetRegistry() { return m_Registry; }

	private:
		entt::registry m_Registry;
		std::vector<GameObject*> m_SceneObjects;
	};
}