#include "Framework/Game.h"
#include "Game/Game2048.h"
#include "Game/Renderer.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game2048::Game2048 game2048;
	Game2048::Renderer renderer;

	Framework::Game game(game2048, renderer);
	// ������
	game.Init();
	// ���s���I���܂Ń��[�v
	game.Run();
	// �I������
	game.Final();

	return 0;
}