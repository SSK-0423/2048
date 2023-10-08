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
		enum class INPUT_DIRECTION
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			NONE
		};

		std::vector<std::vector<unsigned int>> m_grid;
		std::unique_ptr<class Framework::Object> m_testTile;
		std::vector<std::vector<std::unique_ptr<class Framework::Object>>> m_testTiles;

		float m_gridLeft = 0;
		float m_gridTop = 0;

		std::mt19937_64 m_randomEngine;
		std::uniform_real_distribution<> m_randomGenerator;

		INPUT_DIRECTION CheckInputDirection();
		bool UnionAndCheckGameClear(INPUT_DIRECTION direction);
		bool MoveAndCheckGameOver(INPUT_DIRECTION direction);
		void SpawnTile(INPUT_DIRECTION direction);
		
		void TestTileDraw();
	};
}