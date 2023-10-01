#pragma once
#include "Framework/Canvas.h"

namespace Game2048
{
	class TitleSceneCanvas : public Framework::Canvas
	{
	public:
		TitleSceneCanvas();
		~TitleSceneCanvas();

		void Init() override;
		void Final() override;

	private:
		void LoadGameScene();
	};
}