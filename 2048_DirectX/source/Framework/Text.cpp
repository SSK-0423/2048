#include "pch.h"
#include "Text.h"
#include "Object.h"
#include "Transform2D.h"

using namespace DX12Wrapper;

namespace Framework
{
	Text::Text(Object* owner)
		: IComponent(owner), m_fontRenderer(DX12Wrapper::FontRenderer::Instance())
	{
	}
	void Text::Update(float deltaTime)
	{
	}
	void Text::Draw()
	{
		auto transform = m_owner->GetComponent<Transform2D>();
		m_fontRenderer.DrawString(m_text, transform->position, DirectX::Colors::White);
	}
	void Text::SetText(const std::wstring& text)
	{
		m_text = text;
	}
}