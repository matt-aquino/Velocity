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
		for (GameObject* obj : m_SceneObjects)
			delete obj;
	}

	GameObject* Scene::CreateGameObject(const std::string& name)
	{
		return m_SceneObjects.emplace_back(new GameObject(name, this));
	}

	void Scene::OnUpdate(float deltaTime)
	{

	}
}