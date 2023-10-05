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
		std::vector<std::vector<unsigned int>> m_grid;
		std::unique_ptr<class Framework::Object> m_testTile;

		float m_gridLeft = 0;
		float m_gridTop = 0;
	};
}