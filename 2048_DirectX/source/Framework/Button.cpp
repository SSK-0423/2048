#include "pch.h"
#include "Button.h"
#include "Object.h"
#include "Sprite.h"
#include "Transform2D.h"
#include "InputSystem.h"

namespace Framework
{
	Button::Button(Object* owner)
		: IComponent(owner), m_sprite(nullptr), m_onClick(nullptr)
	{
	}
	Button::Button(Object* owner, std::function<void()> onClick, DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 scale)
		: IComponent(owner), m_sprite(nullptr)
	{
		m_onClick = onClick;
		auto transform = owner->GetComponent<Transform2D>();
		transform->position = pos;
		transform->scale = scale;
	}
	bool Button::CheckClick()
	{
		auto& inputSystem = InputSystem::Instance();
		POINT mousePos = inputSystem.GetMousePosition();

		Transform2D* transform = m_owner->GetComponent<Transform2D>();
		float left = transform->position.x - transform->scale.x / 2;
		float right = transform->position.x + transform->scale.x / 2;
		float top = transform->position.y - transform->scale.y / 2;
		float bottom = transform->position.y + transform->scale.y / 2;

		// マウスがボタンの範囲内にあるか
		if (left <= mousePos.x && mousePos.x <= right &&
			top <= mousePos.y && mousePos.y <= bottom)
		{
			// マウスクリック
			auto& inputSystem = InputSystem::Instance();
			if (inputSystem.GetMouseButtonDown(MOUSECODE::LEFT))
			{
				return true;
			}
		}
		return false;
	}
	void Button::Update(float deltaTime)
	{
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
		m_owner->GetComponent<Transform2D>()->position = DirectX::XMFLOAT2(x, y);
	}
	void Button::SetScale(float x, float y)
	{
		m_owner->GetComponent<Transform2D>()->scale = DirectX::XMFLOAT2(x, y);
	}
	void Button::SetSprite(const std::wstring& path)
	{
		if (m_sprite == nullptr)
		{
			m_sprite = std::make_unique<Sprite>(m_owner);
		}
		m_sprite->LoadTexture(path);
	}
	void Button::SetOnClick(std::function<void()> onClick)
	{
		m_onClick = onClick;
	}
}
