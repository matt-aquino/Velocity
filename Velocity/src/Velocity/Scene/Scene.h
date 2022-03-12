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

		GameObject CreateGameObject(std::string& name);
		void OnUpdate(float deltaTime);

	private:
		entt::registry m_Registry;
	};
}