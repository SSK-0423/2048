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
		bool isPlaying = m_window.DispatchWindowMessage();

		while (isPlaying)
		{
			auto currentFrameTime = std::chrono::system_clock::now();
			auto deltaTime
				= std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - m_prevFrameTime).count();

			m_prevFrameTime = std::chrono::system_clock::now();

			// キー入力
			InputSystem::Instance().Update();

			// 更新
			SceneManager::Instance().NowSceneUpdate(deltaTime);

			// 描画
			SceneManager::Instance().NowSceneDraw();

			char buffer[256];
			sprintf_s(buffer, "%lld (ms)\n", deltaTime);
			OutputDebugStringA(buffer);
		}

		return;
	}

	void Game::Final()
	{
		// 終了処理
		SceneManager::Instance().NowSceneFinal();
	}
}

