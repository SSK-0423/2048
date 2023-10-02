#pragma once
#include "Framework/IComponent.h"

namespace Game2048
{
	class TitleSprite : public Framework::IComponent
	{
	public:
		TitleSprite(Framework::Object* owner);
		~TitleSprite();

		void Update(float deltaTime) override;
		void Draw() override;
	};
}