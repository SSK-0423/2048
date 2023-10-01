#include "SceneManager.h"
#include "IRenderer.h"

namespace Framework
{
	void SceneManager::ActiveSceneUpdate(float deltaTime)
	{
		m_scenes[m_activeSceneName]->Update(deltaTime);
	}
	void SceneManager::ActiveSceneDraw(IRenderer& renderer)
	{
		renderer.Render(m_scenes[m_activeSceneName].get());
	}
	void SceneManager::ActiveSceneFinal()
	{
		if (m_scenes[m_activeSceneName] != nullptr)
		{
			m_scenes[m_activeSceneName]->Final();
		}
	}
	void SceneManager::LoadScene(const char* name)
	{
		if (m_scenes[m_activeSceneName] != nullptr)
		{
			m_scenes[m_activeSceneName]->Final();
		}
		m_activeSceneName = name;
		m_scenes[m_activeSceneName]->Init();
	}
}