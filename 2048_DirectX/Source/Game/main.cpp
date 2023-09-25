#include <Windows.h>
#include "Framework/Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameFramework::Game& game = GameFramework::Game::Instance();
	// 初期化
	game.Init();
	// 実行が終わるまでループ
	game.Run();
	// 終了処理
	game.Final();
	return 0;
}