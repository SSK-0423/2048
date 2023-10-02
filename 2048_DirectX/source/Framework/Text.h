#pragma once
#include "IComponent.h"
#include "DX12Wrapper/FontRenderer.h"

#include <DirectXMath.h>

namespace Framework
{
	class Text : public IComponent
	{
	public:
		Text(Object* owner);
		~Text() = default;

		void Update(float deltaTime) override;
		void Draw() override;
		void SetText(const std::wstring& text);
	private:
		std::wstring m_text;
		DX12Wrapper::FontRenderer& m_fontRenderer;
	};
}