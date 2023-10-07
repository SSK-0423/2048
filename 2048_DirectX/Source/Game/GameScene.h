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

		// オブジェクトの描画レイヤー
		enum class DRAW_LAYER
		{
			UI = 0,
			TILE = 1,
			GRID = 2,
			BACKGROUND = 3,
		};
	};
}