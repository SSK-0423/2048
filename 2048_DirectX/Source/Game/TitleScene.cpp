#include "pch.h"
#include "TitleScene.h"
#include "Framework/Sprite.h"

using namespace Framework;

namespace Game2048
{
	void TitleScene::Init()
	{
		// GUIçÏê¨
		std::unique_ptr<GameObject> titleSprite = std::make_unique<GameObject>();
		titleSprite->AddComponent<Sprite>(titleSprite.get());
		titleSprite->GetComponent<Sprite>()->LoadTexture(std::wstring(L"res/Title.png"));

		m_gameObjects.push_back(std::move(titleSprite));

		//MessageBoxA(NULL, "TitleScene", "Debug", MB_OK);
	}
	void TitleScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();

		m_guiObjects.clear();
		m_guiObjects.shrink_to_fit();

		OutputDebugStringA("TitleScene Final\n");
	}
}