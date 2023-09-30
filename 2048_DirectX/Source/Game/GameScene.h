#pragma once
#include "Framework/Scene.h"

namespace Game2048
{
	class GameScene : public Framework::Scene
	{
	public:
		GameScene() = default;
		~GameScene() = default;

		void Init() override;
		void Final() override;
	};
}