#include "pch.h"
#include "TitleScene.h"
#include "Framework/Sprite.h"

#include "TitleSprite.h"

using namespace Framework;

namespace Game2048
{
	void TitleScene::Init()
	{
		// GUIçÏê¨
		std::unique_ptr<GameObject> titleSprite = std::make_unique<GameObject>();
		titleSprite->AddComponent<TitleSprite>(titleSprite.get());

		m_gameObjects.push_back(std::move(titleSprite));
	}
	void TitleScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();

		OutputDebugStringA("TitleScene Final\n");
	}
}