#include "pch.h"
#include "Grid.h"
#include "Tile.h"
#include "GameScene.h"

#include "Framework/Window.h"
#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/SpriteRenderer.h"
#include "Framework/Transform2D.h"
#include "Framework/InputSystem.h"
#include "Framework/Text.h"

constexpr size_t GRID_WIDTH = 4;
constexpr size_t GRID_HEIGHT = 4;
constexpr size_t GRID_WIDTH_SIZE = 600;
constexpr size_t GRID_HEIGHT_SIZE = 600;

using namespace Framework;

namespace Game2048
{
	Grid::Grid(Framework::Object* owner) : IComponent(owner)
	{
		Tile::LoadTileTextures();

		auto windowSize = Window::GetWindowSize();
		DirectX::XMFLOAT2 gridPosition = { windowSize.cx / 2.f, windowSize.cy / 2.f };
		DirectX::XMFLOAT2 gridScale = { GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE };

		// グリッドの背景
		std::unique_ptr<GameObject> gridBackground = std::make_unique<GameObject>();
		Sprite* gridBackgroundSprite = new Sprite(L"res/GridBackground.png");
		auto backGroundRenderer = gridBackground->AddComponent<SpriteRenderer>(gridBackground.get());
		backGroundRenderer->SetSprite(gridBackgroundSprite);
		backGroundRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::GRID_BACKGROUND));
		auto backGroundTransform = gridBackground->GetComponent<Transform2D>();
		backGroundTransform->position = gridPosition;
		backGroundTransform->scale = gridScale;
		m_owner->AddChild(gridBackground);

		// グリッドの線
		std::unique_ptr<GameObject> gridLine = std::make_unique<GameObject>();
		Sprite* gridLineSprite = new Sprite(L"res/GridLine.png");
		auto gridLineRenderer = gridLine->AddComponent<SpriteRenderer>(gridLine.get());
		gridLineRenderer->SetSprite(gridLineSprite);
		gridLineRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::GRID_LINE));
		auto gridLineTransform = gridLine->GetComponent<Transform2D>();
		gridLineTransform->position = gridPosition;
		gridLineTransform->scale = gridScale;
		m_owner->AddChild(gridLine);

		// グリッドの左上座標取得
		m_gridLeft = gridPosition.x - GRID_WIDTH_SIZE / 2.f;
		m_gridTop = gridPosition.y - GRID_HEIGHT_SIZE / 2.f;

		// グリッドの初期化
		m_grid.resize(GRID_HEIGHT);
		std::for_each(m_grid.begin(), m_grid.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		// パネルの初期化
		int tileWidth = GRID_WIDTH_SIZE / GRID_WIDTH;
		int tileHeight = GRID_HEIGHT_SIZE / GRID_HEIGHT;

		// テストタイル初期化
		m_testTiles.resize(GRID_HEIGHT);
		std::for_each(m_testTiles.begin(), m_testTiles.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				m_testTiles[y][x] = std::make_unique<GameObject>();
				auto tile = m_testTiles[y][x]->AddComponent<Tile>(m_testTiles[y][x].get());
				tile->SetScale(tileWidth, tileHeight);
				tile->SetGridPosition(x, y, m_gridLeft, m_gridTop);
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

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				m_testTiles[y][x]->Update(deltaTime);
				if (m_grid[y][x] != 0)
				{
					m_testTiles[y][x]->GetComponent<Tile>()->SetNumber(m_grid[y][x]);
					m_testTiles[y][x]->GetComponent<Tile>()->SetGridPosition(x, y, m_gridLeft, m_gridTop);
				}
			}
		}
	}

	void Grid::Draw()
	{
		TestTileDraw();

		//Utility::DebugLog("---------------------\n");
		////出力
		//for (int y = 0; y < GRID_HEIGHT; y++)
		//{
		//	for (int x = 0; x < GRID_WIDTH; x++)
		//	{
		//		Utility::DebugLog("%4d ", m_grid[y][x]);
		//	}
		//	Utility::DebugLog("\n");
		//}
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
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				// 上端から順にチェック
				for (int y = 0; y < GRID_HEIGHT - 1; y++)
				{
					// 空白マスはスキップ
					if (m_grid[y][x] == 0)
					{
						continue;
					}
					// 下側にマスを見ていって同じ数字があったら合体
					for (int i = y + 1; i < GRID_HEIGHT; i++)
					{
						if (m_grid[y][x] == m_grid[i][x])
						{
							m_grid[y][x] *= 2;
							m_grid[i][x] = 0;

							// 2段階の合体を防ぐ
							continue;
						}
						// 参照したマスに数字がある場合はそこでチェック終了
						else if (m_grid[i][x] != 0)
						{
							break;
						}
					}
				}
			}
			break;

			// 下に移動
		case Grid::INPUT_DIRECTION::DOWN:
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				// 下端から順にチェック
				for (int y = GRID_HEIGHT - 1; y > 0; y--)
				{
					// 空白マスはスキップ
					if (m_grid[y][x] == 0)
					{
						continue;
					}

					// 上側にマスを見ていって同じ数字があったら合体
					for (int i = y - 1; i >= 0; i--)
					{
						if (m_grid[y][x] == m_grid[i][x])
						{
							m_grid[y][x] *= 2;
							m_grid[i][x] = 0;

							// 2段階の合体を防ぐ
							continue;
						}
						// 参照したマスに数字がある場合はそこでチェック終了
						else if (m_grid[i][x] != 0)
						{
							break;
						}
					}
				}
			}
			break;

			// 左に移動
		case Grid::INPUT_DIRECTION::LEFT:
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				// 左端から順にチェック
				for (int x = 0; x < GRID_WIDTH - 1; x++)
				{
					// 空白マスはスキップ
					if (m_grid[y][x] == 0)
					{
						continue;
					}
					// 右側にマスを見ていって同じ数字があったら合体
					for (int i = x + 1; i < GRID_WIDTH; i++)
					{
						if (m_grid[y][x] == m_grid[y][i])
						{
							m_grid[y][x] *= 2;
							m_grid[y][i] = 0;

							// 2段階の合体を防ぐ
							continue;
						}
						// 参照したマスに数字がある場合はそこでチェック終了
						else if (m_grid[y][i] != 0)
						{
							break;
						}
					}
				}
			}
			break;

			// 右に移動
		case Grid::INPUT_DIRECTION::RIGHT:
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				// 右端から順にチェック
				for (int x = GRID_WIDTH - 1; x > 0; x--)
				{
					// 空白マスはスキップ
					if (m_grid[y][x] == 0)
					{
						continue;
					}
					// 左側にマスを見ていって同じ数字があったら合体
					for (int i = x - 1; i >= 0; i--)
					{
						if (m_grid[y][x] == m_grid[y][i])
						{
							m_grid[y][x] *= 2;
							m_grid[y][i] = 0;

							// 2段階の合体を防ぐ
							continue;
						}
						// 参照したマスに数字がある場合はそこでチェック終了
						else if (m_grid[y][i] != 0)
						{
							break;
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
				int random = rand();
				if (random % 100 <= 75)
				{
					m_grid[y][x] = 2;
				}
				else
				{
					m_grid[y][x] = 4;
				}
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
