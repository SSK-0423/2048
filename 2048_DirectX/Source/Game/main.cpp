#include "Framework/Game.h"
#include "Game/Game2048.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game2048::Game2048 game2048;

	Framework::Game& game = Framework::Game::Instance(game2048);
	// 初期化
	game.Init();
	// 実行が終わるまでループ
	game.Run();
	// 終了処理
	game.Final();
	return 0;
}