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

		// グリッド
		std::unique_ptr<GUIObject> grid = std::make_unique<GUIObject>();
		grid->AddComponent<Sprite>(grid.get());
		grid->GetComponent<Sprite>()->LoadTexture(L"res/TitleBackground.png");
		grid->GetComponent<Transform2D>()->scale = { windowSize.cx * 0.5f, windowSize.cy * 0.5f };
		grid->GetComponent<Transform2D>()->position = { windowSize.cx / 2.f, windowSize.cy / 2.f };
		m_guiObjects.push_back(std::move(grid));

		// 背景
		std::unique_ptr<GUIObject> background = std::make_unique<GUIObject>();
		background->AddComponent<Sprite>(background.get());
		background->GetComponent<Sprite>()->LoadTexture(L"res/GameBackground.png");
		background->GetComponent<Transform2D>()->scale = { windowSize.cx * 1.f, windowSize.cy * 1.f };
		m_guiObjects.push_back(std::move(background));


		// 経過時間
		std::unique_ptr<GUIObject> elapsedTimeText = std::make_unique<GUIObject>();
		elapsedTimeText->AddComponent<GameTimer>(elapsedTimeText.get());
		m_guiObjects.push_back(std::move(elapsedTimeText));

		// 操作方法
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
