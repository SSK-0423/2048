#include "pch.h"
#include "GameScene.h"
#include "GameSceneCanvas.h"

namespace Game2048
{
	void GameScene::Init()
	{
		// CanvasçÏê¨
		std::unique_ptr<GameSceneCanvas> gameCanvas = std::make_unique<GameSceneCanvas>();
		gameCanvas->Init();
		m_canvases.push_back(std::move(gameCanvas));
	}
	void GameScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();
	}
}