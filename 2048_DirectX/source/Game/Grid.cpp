#include "pch.h"
#include "Grid.h"
#include "Tile.h"

#include "Framework/Window.h"
#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/SpriteRenderer.h"
#include "Framework/Transform2D.h"
#include "Framework/InputSystem.h"

constexpr size_t GRID_WIDTH = 4;
constexpr size_t GRID_HEIGHT = 4;
constexpr size_t GRID_WIDTH_SIZE = 600;
constexpr size_t GRID_HEIGHT_SIZE = 600;

using namespace Framework;

namespace Game2048
{
	Grid::Grid(Framework::Object* owner) : IComponent(owner)
	{
		// Spriteコンポーネント追加
		auto spriteRenderer = m_owner->AddComponent<SpriteRenderer>(m_owner);
		spriteRenderer->SetSprite(new Sprite(L"res/Grid.png"));

		auto windowSize = Window::GetWindowSize();

		auto transform = m_owner->GetComponent<Transform2D>();
		transform->scale = { GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE };
		transform->position = { windowSize.cx / 2.f, windowSize.cy / 2.f };

		// グリッドの左上座標取得
		m_gridLeft = transform->position.x - GRID_WIDTH_SIZE / 2.f;
		m_gridTop = transform->position.y - GRID_HEIGHT_SIZE / 2.f;

		// グリッドの初期化
		m_grid.resize(GRID_HEIGHT);
		std::for_each(m_grid.begin(), m_grid.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		// パネルの初期化
		int tileWidth = GRID_WIDTH_SIZE / GRID_WIDTH;
		int tileHeight = GRID_HEIGHT_SIZE / GRID_HEIGHT;

		// テストタイル初期化
		m_testTiles.resize(GRID_HEIGHT);
		std::for_each(m_testTiles.begin(), m_testTiles.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		for (int i = 0; i < GRID_HEIGHT; i++)
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				m_testTiles[i][j] = std::make_unique<GameObject>();
				auto tile = m_testTiles[i][j]->AddComponent<Tile>(m_testTiles[i][j].get());
				tile->SetScale(tileWidth, tileHeight);
				tile->SetGridPosition(i, j, m_gridLeft, m_gridTop);
			}
		}

		// 初期タイル生成
		for (int i = 0; i < 2; i++)
		{
			// NONE以外ならなんでもOK
			SpawnTile(INPUT_DIRECTION::LEFT);
		}
	}

	void Grid::Update(float deltaTime)
	{
		INPUT_DIRECTION direction = CheckInputDirection();

		UnionAndCheckGameClear(direction);
		MoveAndCheckGameOver(direction);
		SpawnTile(direction);
	}

	void Grid::Draw()
	{
		TestTileDraw();
		Utility::DebugLog("---------------------\n");
		// 出力
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				Utility::DebugLog("%4d ", m_grid[y][x]);
			}
			Utility::DebugLog("\n");
		}
	}

	Grid::INPUT_DIRECTION Grid::CheckInputDirection()
	{
		auto& input = InputSystem::Instance();

		// 左に移動
		if (input.GetKeyDown(DIK_LEFTARROW))
		{
			return INPUT_DIRECTION::LEFT;
		}
		// 右に移動
		else if (input.GetKeyDown(DIK_RIGHTARROW))
		{
			return INPUT_DIRECTION::RIGHT;
		}
		// 上に移動
		else if (input.GetKeyDown(DIK_UPARROW))
		{
			return INPUT_DIRECTION::UP;
		}
		// 下に移動
		else if (input.GetKeyDown(DIK_DOWNARROW))
		{
			return INPUT_DIRECTION::DOWN;
		}

		return INPUT_DIRECTION::NONE;
	}

	// 合体処理
	bool Grid::UnionAndCheckGameClear(INPUT_DIRECTION direction)
	{
		if (direction == INPUT_DIRECTION::NONE)
		{
			return false;
		}

		switch (direction)
		{
			// 上に移動
		case Grid::INPUT_DIRECTION::UP:
			for (int y = 0; y < GRID_HEIGHT - 1; y++)
			{
				for (int x = 0; x < GRID_WIDTH; x++)
				{
					if (m_grid[y][x] == m_grid[y + 1][x])
					{
						m_grid[y][x] *= 2;
						m_grid[y + 1][x] = 0;
					}
				}
			}
			break;

			// 下に移動
		case Grid::INPUT_DIRECTION::DOWN:
			for (int y = GRID_HEIGHT - 1; y > 0; y--)
			{
				for (int x = 0; x < GRID_WIDTH; x++)
				{
					if (m_grid[y][x] == m_grid[y - 1][x])
					{
						m_grid[y][x] *= 2;
						m_grid[y - 1][x] = 0;
					}
				}
			}
			break;

			// 左に移動
		case Grid::INPUT_DIRECTION::LEFT:
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				for (int x = 0; x < GRID_WIDTH - 1; x++)
				{
					if (m_grid[y][x] == m_grid[y][x + 1])
					{
						m_grid[y][x] *= 2;
						m_grid[y][x + 1] = 0;
					}
				}
			}
			break;

			// 右に移動
		case Grid::INPUT_DIRECTION::RIGHT:
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				for (int x = GRID_WIDTH - 1; x > 0; x--)
				{
					if (m_grid[y][x] == m_grid[y][x - 1])
					{
						m_grid[y][x] *= 2;
						m_grid[y][x - 1] = 0;
					}
				}
			}
			break;

		default:
			break;
		}

		return false;
	}

	// 移動処理
	bool Grid::MoveAndCheckGameOver(INPUT_DIRECTION direction)
	{
		if (direction == INPUT_DIRECTION::NONE)
		{
			return false;
		}

		switch (direction)
		{
			// 上に移動
		case Grid::INPUT_DIRECTION::UP:
			for (int i = 0; i < GRID_HEIGHT - 1; i++)
			{
				for (int y = 0; y < GRID_HEIGHT - 1; y++)
				{
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						if (m_grid[y][x] == 0)
						{
							m_grid[y][x] = m_grid[y + 1][x];
							m_grid[y + 1][x] = 0;
						}
					}
				}
			}
			break;

			// 下に移動
		case Grid::INPUT_DIRECTION::DOWN:
			for (int i = 0; i < GRID_HEIGHT - 1; i++)
			{
				for (int y = GRID_HEIGHT - 1; y > 0; y--)
				{
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						if (m_grid[y][x] == 0)
						{
							m_grid[y][x] = m_grid[y - 1][x];
							m_grid[y - 1][x] = 0;
						}
					}
				}
			}
			break;

			// 左に移動
		case Grid::INPUT_DIRECTION::LEFT:
			for (int i = 0; i < GRID_WIDTH - 1; i++)
			{
				for (int y = 0; y < GRID_HEIGHT; y++)
				{
					for (int x = 0; x < GRID_WIDTH - 1; x++)
					{
						if (m_grid[y][x] == 0)
						{
							m_grid[y][x] = m_grid[y][x + 1];
							m_grid[y][x + 1] = 0;
						}
					}
				}
			}
			break;

			// 右に移動
		case Grid::INPUT_DIRECTION::RIGHT:
			for (int i = 0; i < GRID_WIDTH - 1; i++)
			{
				for (int y = 0; y < GRID_HEIGHT; y++)
				{
					for (int x = GRID_WIDTH - 1; x > 0; x--)
					{
						if (m_grid[y][x] == 0)
						{
							m_grid[y][x] = m_grid[y][x - 1];
							m_grid[y][x - 1] = 0;
						}
					}
				}
			}
			break;

		default:
			break;
		}

		return false;
	}
	void Grid::SpawnTile(INPUT_DIRECTION direction)
	{
		// 入力方向によってスポーン位置が変わる
		// 移動後に移動方向の逆側が3or2マス空いている場合は端もしくは端から2マス目にスポーン
		// それ以外は端にスポーン

		if (direction == INPUT_DIRECTION::NONE)
		{
			return;
		}

		// 空いてるマスにランダムスポーン
		while (true)
		{
			int x = rand() % GRID_WIDTH;
			int y = rand() % GRID_HEIGHT;
			if (m_grid[y][x] == 0)
			{
				m_grid[y][x] = (rand() % 2 + 1) * 2;
				return;
			}
		}
	}
	void Grid::TestTileDraw()
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				if (m_grid[y][x] != 0)
				{
					m_testTiles[y][x]->GetComponent<SpriteRenderer>()->Draw();
				}
			}
		}
	}
}
