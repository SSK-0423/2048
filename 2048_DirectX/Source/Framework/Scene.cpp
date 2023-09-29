#include "Scene.h"
namespace Framework
{
	void Scene::Update(float deltaTime)
	{
		for (auto& obj : m_gameObjects)
		{
			obj.Update(deltaTime);
		}

		for (auto& obj : m_guiObjects)
		{
			obj.Update();
		}
	}
	void Scene::Draw()
	{
		for (auto& obj : m_gameObjects)
		{
			obj.Draw();
		}
		for (auto& obj : m_guiObjects)
		{
			obj.Draw();
		}
	}
}