#pragma once
#include "../Framework/Scene.h"

namespace Game2048
{
	class TitleScene : public Framework::Scene
	{
	public:
		TitleScene() = default;
		~TitleScene() = default;
		
		void Init() override;
		void Final() override;
	};
}