#include <Windows.h>
#include "Framework/Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework::Game& game = Framework::Game::Instance();
	// ������
	game.Init();
	// ���s���I���܂Ń��[�v
	game.Run();
	// �I������
	game.Final();
	return 0;
}