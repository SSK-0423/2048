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
			// �L�[����
			
			// �X�V
			
			// �`��

		}
		return;
	}

	void Game::Final()
	{
		// �I������
	}
}

