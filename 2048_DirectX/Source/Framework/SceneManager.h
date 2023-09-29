#pragma once
#include "Scene.h"

namespace Framework
{
	class SceneManager
	{
	private:
		SceneManager() : m_nowSceneName("") {};
		~SceneManager() = default;
	public:

		static SceneManager& Instance()
		{
			static SceneManager inst;
			return inst;
		}

		void NowSceneUpdate(float deltaTime);

		void NowSceneDraw();

		void NowSceneFinal();

		void LoadScene(const char* name);

		template<class T>
		void AddScene(const char* name)
		{
			m_scenes.insert(std::make_pair(name, std::make_unique<T>()));
		}

	private:
		const char* m_nowSceneName;

		std::unordered_map<const char*, std::unique_ptr<Scene>> m_scenes;
	};
}