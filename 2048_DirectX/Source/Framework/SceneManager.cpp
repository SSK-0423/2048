#include "SceneManager.h"
#include "IRenderer.h"

namespace Framework
{
	void SceneManager::CurrentSceneUpdate(float deltaTime)
	{
		m_scenes[m_currentSceneName]->Update(deltaTime);
	}
	void SceneManager::CurrentSceneDraw(IRenderer& renderer)
	{
		m_scenes[m_currentSceneName]->DrawScene(renderer);
		m_scenes[m_currentSceneName]->DrawUI();
	}
	void SceneManager::CurrentSceneFinal()
	{
		if (m_scenes[m_currentSceneName] != nullptr)
		{
			m_scenes[m_currentSceneName]->Final();
		}
	}
	void SceneManager::LoadScene(const char* name)
	{
		if (m_scenes[m_currentSceneName] != nullptr)
		{
			m_scenes[m_currentSceneName]->Final();
		}
		m_currentSceneName = name;
		m_scenes[m_currentSceneName]->Init();
	}
}