#pragma once
#include "IComponent.h"

namespace Framework
{
	class Sprite : public IComponent
	{
	public:
		Sprite(Object* owner) : IComponent(owner) {};
		~Sprite() = default;
	private:
		// テクスチャ

		// Render
		void Render();

	public:
		void Update(float deltaTime) override;
		void Draw() override;
	};
}