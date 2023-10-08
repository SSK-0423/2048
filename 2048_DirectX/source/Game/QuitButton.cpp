#include "pch.h"
#include "QuitButton.h"

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
	QuitButton::QuitButton(Framework::Object* owner) : IComponent(owner)
	{
		auto windowSize = Window::GetWindowSize();

		m_owner->AddComponent<Button>(m_owner);
		auto button = m_owner->GetComponent<Button>();
		button->SetPosition(windowSize.cx - 100.f, 200.f);
		button->SetScale(200.f, 50.f);
		button->SetOnClick([]() { SceneManager::Instance().LoadScene("Title"); });
		button->SetTexture(L"res/QuitButton.png");
	}
	void QuitButton::Update(float deltaTime)
	{
	}
	void QuitButton::Draw()
	{
	}
}

