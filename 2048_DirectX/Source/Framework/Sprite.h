#pragma once
#include "IComponent.h"

namespace Framework
{
	class Sprite : public IComponent
	{
	public:
		Sprite() = default;
		~Sprite() = default;
	private:
		// テクスチャ

		// Render
		void Render();
	};
}