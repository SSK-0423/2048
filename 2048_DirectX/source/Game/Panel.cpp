#include "pch.h"
#include "Panel.h"

#include "Framework/Object.h"
#include "Framework/Sprite.h"

namespace Game2048
{
	Panel::Panel(Framework::Object* owner) : 
		Framework::IComponent(owner)
	{
		// Sprite�R���|�[�l���g�ǉ�
		auto sprite = m_owner->AddComponent<Framework::Sprite>(m_owner);
	}
	void Panel::Init()
	{
	}
	void Panel::Final()
	{
	}
}