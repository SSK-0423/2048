#include "pch.h"
#include "TitleSceneCanvas.h"

#include "Framework/Object.h"
#include "Framework/Button.h"
#include "Framework/SceneManager.h"
#include "Framework/Window.h"
#include "Framework/Sprite.h"
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

		// スタートボタン
		std::unique_ptr<GUIObject> button = std::make_unique<GUIObject>();
		std::function<void()> func = std::bind(&TitleSceneCanvas::LoadGameScene, this);
		button->AddComponent<Button>(button.get());
		button->GetComponent<Button>()->SetTexture(L"res/StartButton.png");
		button->GetComponent<Button>()->SetPosition(size.cx / 2.f, size.cy * 3.f / 4.f);
		button->GetComponent<Button>()->SetScale(100, 50);
		button->GetComponent<Button>()->SetOnClick(func);
		m_guiObjects.push_back(std::move(button));

		// タイトル
		std::unique_ptr<GUIObject> title = std::make_unique<GUIObject>();
		title->AddComponent<Sprite>(title.get());
		title->GetComponent<Sprite>()->LoadTexture(std::wstring(L"res/Title.png"));
		title->GetComponent<Transform2D>()->position = { size.cx / 2.f, size.cy / 4.f };
		title->GetComponent<Transform2D>()->scale = DirectX::XMFLOAT2(300.f, 200.f);
		m_guiObjects.push_back(std::move(title));

		// 背景
		std::unique_ptr<GUIObject> background = std::make_unique<GUIObject>();
		background->AddComponent<Sprite>(background.get());
		background->GetComponent<Sprite>()->LoadTexture(L"res/TitleBackground.png");
		background->GetComponent<Transform2D>()->scale = { size.cx * 1.f, size.cy * 1.f };
		m_guiObjects.push_back(std::move(background));
	}
	void TitleSceneCanvas::Final()
	{
		m_guiObjects.clear();
		m_guiObjects.shrink_to_fit();
	}
	void TitleSceneCanvas::LoadGameScene()
	{
		SceneManager::Instance().LoadScene("Game");
	}
}