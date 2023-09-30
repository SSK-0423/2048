#include "SceneManager.h"

namespace Framework
{
	void SceneManager::CurrentSceneUpdate(float deltaTime)
	{
		m_currentScene->Update(deltaTime);
	}
	void SceneManager::CurrentSceneDraw()
	{
		m_currentScene->Draw();
	}
	void SceneManager::CurrentSceneFinal()
	{
		if (m_currentScene != nullptr)
		{
			m_currentScene->Final();
		}
	}
	void SceneManager::LoadScene(const char* name)
	{
		CurrentSceneFinal();
		m_currentScene = m_scenes[name].get();
		m_currentScene->Init();
	}
}