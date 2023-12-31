#include "pch.h"
#include "Game2048.h"

#include "Framework/SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace Game2048
{
	void Game2048::Init()
	{
		// シーンの初期化
		auto& sceneManager = Framework::SceneManager::Instance();

		sceneManager.AddScene<TitleScene>("Title");
		sceneManager.AddScene<GameScene>("Game");
		
		sceneManager.LoadScene("Title");
	}
	void Game2048::Final()
	{
	}
}
