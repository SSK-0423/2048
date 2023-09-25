#include "Game.h"
#include "InputSystem.h"
#include "SceneManager.h"

static const TCHAR* NAME = L"2048_DirectX";
static const LONG WIDTH = 1024;
static const LONG HEIGHT = 768;

namespace Framework
{
	void Game::Init()
	{
		m_window.Create(NAME, WIDTH, HEIGHT);
	}

	void Game::Run()
	{
		std::chrono::duration<float> deltaTime = std::chrono::system_clock::now() - m_prevFrameTime;

		m_prevFrameTime = std::chrono::system_clock::now();

		bool isPlaying = m_window.DispatchWindowMessage();
		while (isPlaying)
		{
			// キー入力
			InputSystem::Instance().Update();

			// 更新
			SceneManager::Instance().NowSceneUpdate(deltaTime.count());

			// 描画
			SceneManager::Instance().NowSceneDraw();
		}

		return;
	}

	void Game::Final()
	{
		// 終了処理
		SceneManager::Instance().NowSceneFinal();
	}
}

