#pragma once
#include "Framework/Canvas.h"

namespace Game2048
{
	class GameSceneCanvas : public Framework::Canvas
	{
	public:
		GameSceneCanvas();
		~GameSceneCanvas() = default;

		void Init() override;
		void Final() override;
	};
}