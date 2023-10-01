#include "pch.h"
#include "TitleScene.h"
#include "TitleSprite.h"
#include "TitleSceneCanvas.h"

#include "Framework/Sprite.h"

using namespace Framework;

namespace Game2048
{
	void TitleScene::Init()
	{
		// GUIçÏê¨
		std::unique_ptr<GameObject> titleSprite = std::make_unique<GameObject>();
		titleSprite->AddComponent<TitleSprite>(titleSprite.get());
		m_gameObjects.push_back(std::move(titleSprite));

		// CanvasçÏê¨
		std::unique_ptr<TitleSceneCanvas> titleCanvas = std::make_unique<TitleSceneCanvas>();
		titleCanvas->Init();
		m_canvases.push_back(std::move(titleCanvas));
	}
	void TitleScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();

		m_canvases.clear();
		m_canvases.shrink_to_fit();

		OutputDebugStringA("TitleScene Final\n");
	}
}