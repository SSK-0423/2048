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

		// �O���b�h�̔w�i
		std::unique_ptr<GameObject> gridBackground = std::make_unique<GameObject>();
		Sprite* gridBackgroundSprite = new Sprite(L"res/GridBackground.png");
		auto backGroundRenderer = gridBackground->AddComponent<SpriteRenderer>(gridBackground.get());
		backGroundRenderer->SetSprite(gridBackgroundSprite);
		backGroundRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::GRID_BACKGROUND));
		auto backGroundTransform = gridBackground->GetComponent<Transform2D>();
		backGroundTransform->position = gridPosition;
		backGroundTransform->scale = gridScale;
		m_owner->AddChild(gridBackground);

		// �O���b�h�̐�
		std::unique_ptr<GameObject> gridLine = std::make_unique<GameObject>();
		Sprite* gridLineSprite = new Sprite(L"res/GridLine.png");
		auto gridLineRenderer = gridLine->AddComponent<SpriteRenderer>(gridLine.get());
		gridLineRenderer->SetSprite(gridLineSprite);
		gridLineRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::GRID_LINE));
		auto gridLineTransform = gridLine->GetComponent<Transform2D>();
		gridLineTransform->position = gridPosition;
		gridLineTransform->scale = gridScale;
		m_owner->AddChild(gridLine);

		// �O���b�h�̍�����W�擾
		m_gridLeft = gridPosition.x - GRID_WIDTH_SIZE / 2.f;
		m_gridTop = gridPosition.y - GRID_HEIGHT_SIZE / 2.f;

		// �O���b�h�̏�����
		m_grid.resize(GRID_HEIGHT);
		std::for_each(m_grid.begin(), m_grid.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		// �p�l���̏�����
		int tileWidth = GRID_WIDTH_SIZE / GRID_WIDTH;
		int tileHeight = GRID_HEIGHT_SIZE / GRID_HEIGHT;

		// �e�X�g�^�C��������
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

		// �����^�C������
		for (int i = 0; i < 2; i++)
		{
			// NONE�ȊO�Ȃ�Ȃ�ł�OK
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
		////�o��
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

		// ���Ɉړ�
		if (input.GetKeyDown(DIK_LEFTARROW))
		{
			return INPUT_DIRECTION::LEFT;
		}
		// �E�Ɉړ�
		else if (input.GetKeyDown(DIK_RIGHTARROW))
		{
			return INPUT_DIRECTION::RIGHT;
		}
		// ��Ɉړ�
		else if (input.GetKeyDown(DIK_UPARROW))
		{
			return INPUT_DIRECTION::UP;
		}
		// ���Ɉړ�
		else if (input.GetKeyDown(DIK_DOWNARROW))
		{
			return INPUT_DIRECTION::DOWN;
		}

		return INPUT_DIRECTION::NONE;
	}

	// ���̏���
	bool Grid::UnionAndCheckGameClear(INPUT_DIRECTION direction)
	{
		if (direction == INPUT_DIRECTION::NONE)
		{
			return false;
		}

		switch (direction)
		{
			// ��Ɉړ�
		case Grid::INPUT_DIRECTION::UP:
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				// ��[���珇�Ƀ`�F�b�N
				for (int y = 0; y < GRID_HEIGHT - 1; y++)
				{
					// �󔒃}�X�̓X�L�b�v
					if (m_grid[y][x] == 0)
					{
						continue;
					}
					// �����Ƀ}�X�����Ă����ē����������������獇��
					for (int i = y + 1; i < GRID_HEIGHT; i++)
					{
						if (m_grid[y][x] == m_grid[i][x])
						{
							m_grid[y][x] *= 2;
							m_grid[i][x] = 0;

							// 2�i�K�̍��̂�h��
							continue;
						}
						// �Q�Ƃ����}�X�ɐ���������ꍇ�͂����Ń`�F�b�N�I��
						else if (m_grid[i][x] != 0)
						{
							break;
						}
					}
				}
			}
			break;

			// ���Ɉړ�
		case Grid::INPUT_DIRECTION::DOWN:
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				// ���[���珇�Ƀ`�F�b�N
				for (int y = GRID_HEIGHT - 1; y > 0; y--)
				{
					// �󔒃}�X�̓X�L�b�v
					if (m_grid[y][x] == 0)
					{
						continue;
					}

					// �㑤�Ƀ}�X�����Ă����ē����������������獇��
					for (int i = y - 1; i >= 0; i--)
					{
						if (m_grid[y][x] == m_grid[i][x])
						{
							m_grid[y][x] *= 2;
							m_grid[i][x] = 0;

							// 2�i�K�̍��̂�h��
							continue;
						}
						// �Q�Ƃ����}�X�ɐ���������ꍇ�͂����Ń`�F�b�N�I��
						else if (m_grid[i][x] != 0)
						{
							break;
						}
					}
				}
			}
			break;

			// ���Ɉړ�
		case Grid::INPUT_DIRECTION::LEFT:
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				// ���[���珇�Ƀ`�F�b�N
				for (int x = 0; x < GRID_WIDTH - 1; x++)
				{
					// �󔒃}�X�̓X�L�b�v
					if (m_grid[y][x] == 0)
					{
						continue;
					}
					// �E���Ƀ}�X�����Ă����ē����������������獇��
					for (int i = x + 1; i < GRID_WIDTH; i++)
					{
						if (m_grid[y][x] == m_grid[y][i])
						{
							m_grid[y][x] *= 2;
							m_grid[y][i] = 0;

							// 2�i�K�̍��̂�h��
							continue;
						}
						// �Q�Ƃ����}�X�ɐ���������ꍇ�͂����Ń`�F�b�N�I��
						else if (m_grid[y][i] != 0)
						{
							break;
						}
					}
				}
			}
			break;

			// �E�Ɉړ�
		case Grid::INPUT_DIRECTION::RIGHT:
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				// �E�[���珇�Ƀ`�F�b�N
				for (int x = GRID_WIDTH - 1; x > 0; x--)
				{
					// �󔒃}�X�̓X�L�b�v
					if (m_grid[y][x] == 0)
					{
						continue;
					}
					// �����Ƀ}�X�����Ă����ē����������������獇��
					for (int i = x - 1; i >= 0; i--)
					{
						if (m_grid[y][x] == m_grid[y][i])
						{
							m_grid[y][x] *= 2;
							m_grid[y][i] = 0;

							// 2�i�K�̍��̂�h��
							continue;
						}
						// �Q�Ƃ����}�X�ɐ���������ꍇ�͂����Ń`�F�b�N�I��
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

	// �ړ�����
	bool Grid::MoveAndCheckGameOver(INPUT_DIRECTION direction)
	{
		if (direction == INPUT_DIRECTION::NONE)
		{
			return false;
		}

		switch (direction)
		{
			// ��Ɉړ�
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

			// ���Ɉړ�
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

			// ���Ɉړ�
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

			// �E�Ɉړ�
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
		// ���͕����ɂ���ăX�|�[���ʒu���ς��
		// �ړ���Ɉړ������̋t����3or2�}�X�󂢂Ă���ꍇ�͒[�������͒[����2�}�X�ڂɃX�|�[��
		// ����ȊO�͒[�ɃX�|�[��

		if (direction == INPUT_DIRECTION::NONE)
		{
			return;
		}

		// �󂢂Ă�}�X�Ƀ����_���X�|�[��
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
