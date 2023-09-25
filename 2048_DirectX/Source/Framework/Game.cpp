#include "Game.h"

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
			// キー入力
			
			// 更新
			
			// 描画

		}
		return;
	}

	void Game::Final()
	{
		// 終了処理
	}
}

