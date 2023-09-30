#include "Framework/Game.h"
#include "Game/Game2048.h"
#include "Game/Renderer.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game2048::Game2048 game2048;
	Game2048::Renderer renderer;

	Framework::Game game(game2048, renderer);
	// 初期化
	game.Init();
	// 実行が終わるまでループ
	game.Run();
	// 終了処理
	game.Final();

	return 0;
}