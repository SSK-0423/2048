#include "GameObject.h"
#include "Transform2D.h"

namespace Framework
{
	void GameObject::Update(float deltaTime)
	{
		for (auto& component : m_components)
		{
			component->Update(deltaTime);
		}
	}
	void GameObject::Draw()
	{
		for (auto& component : m_components)
		{
			component->Draw();
		}
	}
}