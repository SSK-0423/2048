#include "pch.h"
#include "TitleSceneCanvas.h"

#include "Framework/Object.h"
#include "Framework/Button.h"
#include "Framework/SceneManager.h"

using namespace Framework;

namespace Game2048
{
	TitleSceneCanvas::TitleSceneCanvas()
	{
	}
	TitleSceneCanvas::~TitleSceneCanvas()
	{
	}
	void TitleSceneCanvas::Init()
	{
		// ƒ{ƒ^ƒ“’Ç‰Á
		std::unique_ptr<GUIObject> button = std::make_unique<GUIObject>();
		std::function<void()> func = std::bind(&TitleSceneCanvas::LoadGameScene, this);
		button->AddComponent<Button>(
			button.get(), func, DirectX::XMFLOAT2(100, 100), DirectX::XMFLOAT2(100, 100));
		button->GetComponent<Button>()->SetSprite(L"res/StartButton.png");
		m_guiObjects.push_back(std::move(button));
	}
	void TitleSceneCanvas::Final()
	{
		m_guiObjects.clear();
		m_guiObjects.shrink_to_fit();
	}
	void TitleSceneCanvas::LoadGameScene()
	{
		SceneManager::Instance().LoadScene("GameScene");
	}
}