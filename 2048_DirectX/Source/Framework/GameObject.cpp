#include "GameObject.h"
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