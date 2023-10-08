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

		// �I�u�W�F�N�g�̕`�惌�C���[
		enum class DRAW_LAYER
		{
			UI = 0,
			GRID_LINE = 1,
			TILE = 2,
			GRID_BACKGROUND = 3,
			BACKGROUND = 4,
		};
	};
}