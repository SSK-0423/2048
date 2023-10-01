#include "pch.h"
#include "Button.h"
#include "Object.h"
#include "Sprite.h"
#include "Transform2D.h"
#include "InputSystem.h"

namespace Framework
{
	Button::Button(Object* owner, std::function<void()> onClick, DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 scale)
		: IComponent(owner), m_sprite(nullptr)
	{
		m_onClick = onClick;
		m_transform = owner->GetComponent<Transform2D>();
		m_transform->position = pos;
		m_transform->scale = scale;
	}
	bool Button::CheckClick()
	{
		auto& inputSystem = InputSystem::Instance();
		POINT mousePos = inputSystem.GetMousePosition();

		// マウスがボタンの範囲内にあるか
		Transform2D* transform = m_owner->GetComponent<Transform2D>();
		float left = transform->position.x - transform->scale.x / 2;
		float right = transform->position.x + transform->scale.x / 2;
		float top = transform->position.y - transform->scale.y / 2;
		float bottom = transform->position.y + transform->scale.y / 2;

		if (left <= mousePos.x && mousePos.x <= right &&
			top <= mousePos.y && mousePos.y <= bottom)
		{
			return true;
		}
		return false;
	}
	void Button::Update(float deltaTime)
	{
		//// マウスクリックテスト
		//auto& inputSystem = InputSystem::Instance();
		//if (inputSystem.GetMouseButtonDown(MOUSECODE::LEFT))
		//{
		//	Utility::DebugLog("Left Click\n");
		//}

		if (CheckClick())
		{
			m_onClick();
		}
	}
	void Button::Draw()
	{
		if (m_sprite != nullptr)
			m_sprite->Draw();
	}
	void Button::SetPosition(float x, float y)
	{
		m_transform->position = DirectX::XMFLOAT2(x, y);
	}
	void Button::SetScale(float x, float y)
	{
		m_transform->scale = DirectX::XMFLOAT2(x, y);
	}
	void Button::SetSprite(const std::wstring& path)
	{
		if (m_sprite == nullptr)
		{
			m_sprite = std::make_unique<Sprite>(m_owner);
		}
		m_sprite->LoadTexture(path);
	}
}
