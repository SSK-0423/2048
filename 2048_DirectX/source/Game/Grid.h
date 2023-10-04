#pragma once
#include "Framework/IComponent.h"

namespace Game2048
{
	class Grid : public Framework::IComponent
	{
	public:
		Grid(Framework::Object* owner);
		~Grid() = default;

		void Update(float deltaTime) override;
		void Draw() override;

	private:
		std::vector<std::vector<int>> m_grid;
	};
}