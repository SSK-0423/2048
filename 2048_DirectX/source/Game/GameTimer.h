#pragma once
#include "Framework/IComponent.h"

namespace Game2048
{
	class GameTimer : public Framework::IComponent
	{
	public:
		GameTimer(Framework::Object* owner);
		~GameTimer() = default;

		void Update(float deltaTime) override;
		void Draw() override;
	private:
		float m_elapsedTime = 0.f;
	};
}
