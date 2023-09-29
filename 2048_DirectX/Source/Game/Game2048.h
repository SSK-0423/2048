#pragma once
#include <Framework/GameImpl.h>

namespace Game2048
{
	class Game2048 : public Framework::GameImpl
	{
	public:
		Game2048() = default;
		~Game2048() = default;

		void Init() override;
		void Final() override;
	};
}