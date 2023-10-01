#include "pch.h"
#include "TitleSprite.h"

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
		m_owner->GetComponent<Transform2D>()->position.x = 100;
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