#include "pch.h"
#include "TitleSprite.h"

#include "Framework/Window.h"
#include "Framework/Sprite.h"
#include "Framework/Transform2D.h"
#include "Framework/Object.h"

using namespace Framework;

namespace Game2048
{
	TitleSprite::TitleSprite(Framework::Object* owner) : IComponent::IComponent(owner)
	{
		m_owner->AddComponent<Sprite>(m_owner);
		m_owner->GetComponent<Sprite>()->LoadTexture(std::wstring(L"res/Title.png"));

		auto windowSize = Window::GetWindowSize();
		Transform2D* transform = m_owner->GetComponent<Transform2D>();
		transform->position.x = windowSize.cx / 2.f;
		transform->position.y = windowSize.cy / 4.f;
		transform->scale = DirectX::XMFLOAT2(300.f, 200.f);
	}
	TitleSprite::~TitleSprite()
	{
	}
	void TitleSprite::Update(float deltaTime)
	{
	}
	void TitleSprite::Draw()
	{}
}