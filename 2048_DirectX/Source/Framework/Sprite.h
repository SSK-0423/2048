#pragma once
#include "IComponent.h"
#include "DX12Wrapper/Texture.h"

namespace Framework
{
	class Sprite : public IComponent
	{
	public:
		Sprite(Object* owner) : IComponent(owner) {};
		~Sprite() = default;

	private:
		// テクスチャ
		DX12Wrapper::Texture texture;

		// Render
		void Render();

	public:
		void LoadTexture(const std::wstring& path);
		void Update(float deltaTime) override;
		void Draw() override;
	};
}