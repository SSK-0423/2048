#include "pch.h"
#include "Canvas.h"

namespace Framework
{
	void Canvas::Update(float deltaTime)
	{
		for (auto& child : m_guiObjects)
		{
			child->Update(deltaTime);
		}
	}
	void Canvas::Draw()
	{
		for (auto& child : m_guiObjects)
		{
			child->Draw();
		}
	}
}