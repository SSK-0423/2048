#include "pch.h"
#include "GameScene.h"

namespace Game2048
{
	void GameScene::Init()
	{
		MessageBoxA(NULL, "GameScene", "Debug", MB_OK);
	}
	void GameScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();

		m_guiObjects.clear();
		m_guiObjects.shrink_to_fit();
	}
}