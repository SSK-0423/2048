#include "Framework/Game.h"
#include "Game/Game2048.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game2048::Game2048 game2048;

	Framework::Game& game = Framework::Game::Instance(game2048);
	// ������
	game.Init();
	// ���s���I���܂Ń��[�v
	game.Run();
	// �I������
	game.Final();
	return 0;
}