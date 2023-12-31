#include "pch.h"
#include "TitleSceneCanvas.h"
#include "PressEnterText.h"

#include "Framework/Object.h"
#include "Framework/Button.h"
#include "Framework/SceneManager.h"
#include "Framework/Window.h"
#include "Framework/Sprite.h"
#include "Framework/SpriteRenderer.h"
#include "Framework/Text.h"
#include "Framework/Transform2D.h"

using namespace Framework;

namespace Game2048
{
	TitleSceneCanvas::TitleSceneCanvas()
	{
	}
	TitleSceneCanvas::~TitleSceneCanvas()
	{
		Final();
	}
	void TitleSceneCanvas::Init()
	{
		auto size = Window::GetWindowSize();

		// 背景
		std::unique_ptr<GUIObject> background = std::make_unique<GUIObject>();
		Sprite* backgroundSprite = new Sprite(L"res/TitleBackground.png");
		background->AddComponent<SpriteRenderer>(background.get());
		background->GetComponent<SpriteRenderer>()->SetSprite(backgroundSprite);
		background->GetComponent<SpriteRenderer>()->SetDrawMode(SPRITE_DRAW_MODE::GUI);
		background->GetComponent<Transform2D>()->position = { size.cx / 2.f, size.cy / 2.f };
		background->GetComponent<Transform2D>()->scale = { size.cx * 1.f, size.cy * 1.f };
		m_guiObjects.push_back(std::move(background));

		// タイトルテキストの輪郭線
		std::unique_ptr<GUIObject> text = std::make_unique<GUIObject>();
		text->AddComponent<Text>(text.get());
		text->GetComponent<Text>()->SetText(L"2048");
		text->GetComponent<Text>()->SetPosition({ size.cx / 6.f, size.cy / 8.f });
		text->GetComponent<Text>()->SetScale(2.05f);
		text->GetComponent<Text>()->SetColor(DirectX::Colors::Black);
		m_guiObjects.push_back(std::move(text));

		// タイトルテキスト
		std::unique_ptr<GUIObject> titleText = std::make_unique<GUIObject>();
		titleText->AddComponent<Text>(titleText.get());
		titleText->GetComponent<Text>()->SetText(L"2048");
		titleText->GetComponent<Text>()->SetPosition({ size.cx / 6.f, size.cy / 8.f });
		titleText->GetComponent<Text>()->SetScale(2.f);
		titleText->GetComponent<Text>()->SetColor(DirectX::Colors::OrangeRed);
		m_guiObjects.push_back(std::move(titleText));

		// スタートテキスト
		std::unique_ptr<GUIObject> pressEnterText = std::make_unique<GUIObject>();
		pressEnterText->AddComponent<PressEnterText>(pressEnterText.get());
		m_guiObjects.push_back(std::move(pressEnterText));
	}
	void TitleSceneCanvas::Final()
	{
		m_guiObjects.clear();
		m_guiObjects.shrink_to_fit();
	}
}