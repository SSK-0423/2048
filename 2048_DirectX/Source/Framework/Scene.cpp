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
	void Scene::DrawScene(IRenderer& renderer)
	{
		renderer.Render(m_gameObjects);
	}
	void Scene::DrawUI()
	{
		for (auto& canvas : m_canvases)
		{
			canvas->Draw();
		}
	}
}