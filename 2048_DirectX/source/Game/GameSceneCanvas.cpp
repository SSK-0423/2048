#include "pch.h"
#include "GameSceneCanvas.h"
#include "GameTimer.h"

#include "Framework/Object.h"
#include "Framework/Button.h"
#include "Framework/SceneManager.h"
#include "Framework/Window.h"
#include "Framework/Sprite.h"
#include "Framework/Text.h"
#include "Framework/Transform2D.h"

using namespace Framework;

namespace Game2048
{
	GameSceneCanvas::GameSceneCanvas()
	{
	}
	void GameSceneCanvas::Init()
	{
		auto windowSize = Window::GetWindowSize();

		// åoâﬂéûä‘
		std::unique_ptr<GUIObject> elapsedTimeText = std::make_unique<GUIObject>();
		elapsedTimeText->AddComponent<GameTimer>(elapsedTimeText.get());
		m_guiObjects.push_back(std::move(elapsedTimeText));

		// ëÄçÏï˚ñ@
		std::unique_ptr<GUIObject> howToPlayText = std::make_unique<GUIObject>();
		howToPlayText->AddComponent<Text>(howToPlayText.get());
		howToPlayText->GetComponent<Text>()->SetScale(0.25f);
		howToPlayText->GetComponent<Text>()->SetColor(DirectX::Colors::Black);
		howToPlayText->GetComponent<Text>()->SetPosition({ windowSize.cx - 250.f, windowSize.cy - 50.f });
		howToPlayText->GetComponent<Text>()->SetText(L"Use Arrow Keys");
		m_guiObjects.push_back(std::move(howToPlayText));

	}
	void GameSceneCanvas::Final()
	{
	}
}
