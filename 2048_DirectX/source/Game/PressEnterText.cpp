#include "pch.h"
#include "PressEnterText.h"
#include "Framework/Object.h"
#include "Framework/Transform2D.h"
#include "Framework/Text.h"
#include "Framework/Window.h"
#include "Framework/InputSystem.h"
#include "Framework/SceneManager.h"

#include "Utility/EngineUtility.h"

using namespace Framework;

namespace Game2048
{
	PressEnterText::PressEnterText(Object* owner)
		: IComponent(owner)
	{
		auto windowSize = Window::GetWindowSize();

		// �e�L�X�g�ǉ�
		auto text = owner->AddComponent<Text>(owner);
		text->SetText(L"Press Enter");
		text->SetColor(DirectX::Colors::White);
		text->SetPosition({ windowSize.cx / 3.f, windowSize.cy * 2.5f / 4.f });
		text->SetScale(0.5f);
	}
	void PressEnterText::Update(float deltaTime)
	{
		// �_��
		auto text = m_owner->GetComponent<Text>();
		m_elapsedTime += deltaTime;

		// 1�b���Ƃɓ_��
		if (static_cast<int>(floor(m_elapsedTime)) % 2 == 0)
		{
			text->SetColor(DirectX::Colors::Black);
		}
		else
		{
			text->SetColor(DirectX::Colors::Transparent);
		}

		Utility::DebugLog("elapsedTime %f (s)", floor(m_elapsedTime));

		// �G���^�[�L�[�������ꂽ��Q�[���V�[����
		if (InputSystem::Instance().GetKeyDown(DIK_RETURN))
		{
			SceneManager::Instance().LoadScene("Game");
		}
	}
	void PressEnterText::Draw()
	{}
}