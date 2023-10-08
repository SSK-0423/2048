#pragma once
#include "Framework/IComponent.h"


/// 
/// Grid内にゲーム全体を管理する機能が入ってしまっている
/// 
/// 
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

		enum class GAME_STATE
		{
			PLAYING,
			GAME_OVER,
			GAME_CLEAR
		};
		GAME_STATE m_gameState = GAME_STATE::PLAYING;

		std::vector<std::vector<unsigned int>> m_grid;
		std::vector<std::vector<std::unique_ptr<class Framework::Object>>> m_tiles;
		std::unique_ptr<class Framework::Object> m_gameClearText;
		std::unique_ptr<class Framework::Object> m_gameOverText;

		float m_gridLeft = 0;
		float m_gridTop = 0;

		std::mt19937_64 m_randomEngine;
		std::uniform_real_distribution<> m_randomGenerator;

		void Playing(float deltaTime);
		void GameClear(float deltaTime);
		void GameOver(float deltaTime);

		INPUT_DIRECTION CheckInputDirection();
		bool Union(INPUT_DIRECTION direction);
		bool Move(INPUT_DIRECTION direction);
		void SpawnTile(INPUT_DIRECTION direction);
		void UpdateTile(float deltaTime);

		bool CheckGameClear();
		bool CheckGameOver();

		void TileDraw();
	};
}