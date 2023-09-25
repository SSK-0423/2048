#pragma once
#include <map>
#include "Scene.h"

namespace Framework
{
	class SceneManager
	{
	private:
		SceneManager() = default;
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

	private:
		const char* m_nowSceneName;

		std::map<const char*, std::unique_ptr<Scene>> m_scenes;
	};
}