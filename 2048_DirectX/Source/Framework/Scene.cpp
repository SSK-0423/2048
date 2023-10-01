#include "Scene.h"
#include "IRenderer.h"

namespace Framework
{
	void Scene::Update(float deltaTime)
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Update(deltaTime);
		}

		for (auto& canvas : m_canvases)
		{
			canvas->Update(deltaTime);
		}
	}
	const std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects() const
	{
		return m_gameObjects;
	}
	const std::vector<std::unique_ptr<Canvas>>& Scene::GetCanvases() const
	{
		return m_canvases;
	}
}