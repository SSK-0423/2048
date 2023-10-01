#pragma once
#include "IComponent.h"
#include <DirectXMath.h>

namespace Framework
{
	class Button : public IComponent
	{
	public:
		Button(Object* owner);
		Button(Object* owner, std::function<void()> onClick, DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 scale);
		~Button() = default;

	private:
		std::unique_ptr<class Sprite> m_sprite;
		//std::unique_ptr<class Text> m_text;
		std::function<void()> m_onClick;

		bool CheckClick();
	public:
		void Update(float deltaTime) override;
		void Draw() override;
		void SetPosition(float x, float y);
		void SetScale(float x, float y);
		void SetSprite(const std::wstring& path);
		void SetOnClick(std::function<void()> onClick);
	};
}