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
		// �e�N�X�`��

		// Render
		void Render();
	};
}