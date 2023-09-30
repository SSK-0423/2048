#include "pch.h"
#include "TitleScene.h"
#include "../Framework/Sprite.h"

namespace Game2048
{
	void TitleScene::Init()
	{
		// GUIì¬
		Framework::GameObject* titleSprite = new Framework::GameObject();
		titleSprite->AddComponent<Framework::Sprite>(titleSprite);

		MessageBoxA(NULL, "TitleScene", "Debug", MB_OK);
	}
	void TitleScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();

		m_guiObjects.clear();
		m_guiObjects.shrink_to_fit();
	}
}