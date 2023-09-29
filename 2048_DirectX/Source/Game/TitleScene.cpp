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

		Framework::Sprite* spriteComponent = titleSprite->GetComponent<Framework::Sprite>();
	}
	void TitleScene::Final()
	{
	}
}