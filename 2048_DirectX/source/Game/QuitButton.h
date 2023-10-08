#pragma once
#include "Framework/IComponent.h"

namespace Game2048
{
	class QuitButton : public Framework::IComponent
	{
	public:
		QuitButton(class Framework::Object* owner);
		~QuitButton() = default;

		void Update(float deltaTime) override;
		void Draw() override;
	};
}