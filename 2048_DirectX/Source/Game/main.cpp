#include <Windows.h>
#include "Framework/Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework::Game& game = Framework::Game::Instance();
	// 初期化
	game.Init();
	// 実行が終わるまでループ
	game.Run();
	// 終了処理
	game.Final();
	return 0;
}