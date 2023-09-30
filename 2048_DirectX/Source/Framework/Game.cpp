#include "Game.h"
#include "GameImpl.h"
#include "IRenderer.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "DX12Wrapper/Dx12GraphicsEngine.h"

static const TCHAR* NAME = L"2048_DirectX";
static const LONG WIDTH = 1024;
static const LONG HEIGHT = 768;

using namespace Utility;

namespace Framework
{
	void Game::Init()
	{
		m_window.Create(NAME, WIDTH, HEIGHT);

		RESULT result = InputSystem::Instance().Init(m_window.GetHwnd());
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "InputSystemの初期化に失敗", "エラー", MB_OK);
		}

		result = DX12Wrapper::Dx12GraphicsEngine::Instance().Init(m_window.GetHwnd(), WIDTH, HEIGHT);
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "Dx12GraphicsEngineの初期化に失敗", "エラー", MB_OK);
		}

		m_gameImpl.Init();
	}

	void Game::Run()
	{
		bool isPlaying = m_window.DispatchWindowMessage();

		auto& sceneManager = SceneManager::Instance();

		while (isPlaying)
		{
			auto currentFrameTime = std::chrono::system_clock::now();
			auto deltaTime
				= std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - m_prevFrameTime).count();

			m_prevFrameTime = std::chrono::system_clock::now();

			// キー入力
			InputSystem::Instance().Update();

			// 更新
			sceneManager.CurrentSceneUpdate(deltaTime);

			// 描画
			sceneManager.CurrentSceneDraw(m_renderer);
		}

		return;
	}

	void Game::Final()
	{
		// 終了処理
		SceneManager::Instance().CurrentSceneFinal();

		m_gameImpl.Final();
	}
}

