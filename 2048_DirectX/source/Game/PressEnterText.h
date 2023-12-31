#pragma once
#include "Framework/IComponent.h"

namespace Game2048
{
	class PressEnterText : public Framework::IComponent
	{
	public:
		PressEnterText(class Framework::Object* owner);
		~PressEnterText() = default;

		void Update(float deltaTime) override;
		void Draw() override;
	private:
		float m_elapsedTime = 0.f;
	};
}