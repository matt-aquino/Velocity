#include "vlpch.h"
#include "Scene.h"
#include "GameObject.h"

namespace Velocity
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	GameObject Scene::CreateGameObject(std::string& name)
	{
		GameObject object = { name, m_Registry.create(), this };
		return object;
	}

	void Scene::OnUpdate(float deltaTime)
	{

	}
}