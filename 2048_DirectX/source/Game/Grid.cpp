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
constexpr unsigned int GAME_CLEAR_NUMBER = 2048;

using namespace Framework;

namespace Game2048
{
	Grid::Grid(Framework::Object* owner) : IComponent(owner)
	{
		Tile::LoadTileTextures();

		auto windowSize = Window::GetWindowSize();
		DirectX::XMFLOAT2 windowCenter = { windowSize.cx / 2.f, windowSize.cy / 2.f };
		DirectX::XMFLOAT2 gridScale = { GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE };

		// �O���b�h�̔w�i
		std::unique_ptr<GameObject> gridBackground = std::make_unique<GameObject>();
		Sprite* gridBackgroundSprite = new Sprite(L"res/GridBackground.png");
		auto backGroundRenderer = gridBackground->AddComponent<SpriteRenderer>(gridBackground.get());
		backGroundRenderer->SetSprite(gridBackgroundSprite);
		backGroundRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::GRID_BACKGROUND));
		auto backGroundTransform = gridBackground->GetComponent<Transform2D>();
		backGroundTransform->position = windowCenter;
		backGroundTransform->scale = gridScale;
		m_owner->AddChild(gridBackground);

		// �O���b�h�̐�
		std::unique_ptr<GameObject> gridLine = std::make_unique<GameObject>();
		Sprite* gridLineSprite = new Sprite(L"res/GridLine.png");
		auto gridLineRenderer = gridLine->AddComponent<SpriteRenderer>(gridLine.get());
		gridLineRenderer->SetSprite(gridLineSprite);
		gridLineRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::GRID_LINE));
		auto gridLineTransform = gridLine->GetComponent<Transform2D>();
		gridLineTransform->position = windowCenter;
		gridLineTransform->scale = gridScale;
		m_owner->AddChild(gridLine);

		// �O���b�h�̍�����W�擾
		m_gridLeft = windowCenter.x - GRID_WIDTH_SIZE / 2.f;
		m_gridTop = windowCenter.y - GRID_HEIGHT_SIZE / 2.f;

		// �O���b�h�̏�����
		m_grid.resize(GRID_HEIGHT);
		std::for_each(m_grid.begin(), m_grid.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		// �Q�[���N���A�e�L�X�g
		m_gameClearText = std::make_unique<GameObject>();
		m_gameClearText->SetActive(false);
		auto spriteRenderer = m_gameClearText->AddComponent<SpriteRenderer>(m_gameClearText.get());
		spriteRenderer->SetSprite(new Sprite(L"res/GameClearText.png", SPRITE_PIVOT::TOP_LEFT));
		spriteRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::UI));
		spriteRenderer->SetDrawMode(SPRITE_DRAW_MODE::GUI);
		auto transform = m_gameClearText->GetComponent<Transform2D>();
		transform->scale = { windowSize.cx * 1.f, windowSize.cy * 1.f };

		// �Q�[���I�[�o�[�e�L�X�g
		m_gameOverText = std::make_unique<GameObject>();
		m_gameOverText->SetActive(false);
		spriteRenderer = m_gameOverText->AddComponent<SpriteRenderer>(m_gameOverText.get());
		spriteRenderer->SetSprite(new Sprite(L"res/GameOverText.png", SPRITE_PIVOT::TOP_LEFT));
		spriteRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::UI));
		spriteRenderer->SetDrawMode(SPRITE_DRAW_MODE::GUI);
		transform = m_gameOverText->GetComponent<Transform2D>();
		transform->scale = { windowSize.cx * 1.f, windowSize.cy * 1.f };

		// �p�l���̏�����
		int tileWidth = GRID_WIDTH_SIZE / GRID_WIDTH;
		int tileHeight = GRID_HEIGHT_SIZE / GRID_HEIGHT;

		// �e�X�g�^�C��������
		m_tiles.resize(GRID_HEIGHT);
		std::for_each(m_tiles.begin(), m_tiles.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				m_tiles[y][x] = std::make_unique<GameObject>();
				auto tile = m_tiles[y][x]->AddComponent<Tile>(m_tiles[y][x].get());
				tile->SetScale(tileWidth, tileHeight);
				tile->SetGridPosition(x, y, m_gridLeft, m_gridTop);
			}
		}

		// ���ݎ���(ms)���V�[�h�l�Ƃ��ė����������������
		auto now = std::chrono::system_clock::now();
		auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
		m_randomEngine = std::mt19937_64(nowMs);
		m_randomGenerator = std::uniform_real_distribution<>(0, 1);

		// �����^�C������
		for (int i = 0; i < 2; i++)
		{
			// NONE�ȊO�Ȃ�Ȃ�ł�OK
			SpawnTile(INPUT_DIRECTION::LEFT);
		}
	}

	void Grid::Update(float deltaTime)
	{
		switch (m_gameState)
		{
		case Game2048::Grid::GAME_STATE::PLAYING:
			Playing(deltaTime);
			break;
		case Game2048::Grid::GAME_STATE::GAME_OVER:
			GameOver(deltaTime);
			break;
		case Game2048::Grid::GAME_STATE::GAME_CLEAR:
			GameClear(deltaTime);
			break;
		default:
			break;
		}
	}

	void Grid::Draw()
	{
		TileDraw();
	}

	void Grid::Playing(float deltaTime)
	{
		INPUT_DIRECTION direction = CheckInputDirection();

		Union(direction);
		Move(direction);

		UpdateTile(deltaTime);

		if (CheckGameClear())
		{
			m_gameState = GAME_STATE::GAME_CLEAR;
		}
		else if (CheckGameOver())
		{
			m_gameState = GAME_STATE::GAME_OVER;
		}
	}

	void Grid::GameClear(float deltaTime)
	{
		// �{����Canvas�ɏ�������
		//�Q�[���N���A������\��
		if (m_gameClearText != nullptr)
		{
			m_gameClearText->SetActive(true);
			m_owner->AddChild(m_gameClearText);
		}
	}

	void Grid::GameOver(float deltaTime)
	{
		// �{����Canvas�ɏ�������
		// �Q�[���I�[�o�[������\��
		if (m_gameOverText != nullptr)
		{
			m_gameOverText->SetActive(true);
			m_owner->AddChild(m_gameOverText);
		}
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
	void Grid::Union(INPUT_DIRECTION direction)
	{
		if (direction == INPUT_DIRECTION::NONE)
		{
			return;
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
	}
	// �ړ�����
	void Grid::Move(INPUT_DIRECTION direction)
	{
		if (direction == INPUT_DIRECTION::NONE)
		{
			return;
		}
		bool canMove = false;

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
							canMove = true;
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
							canMove = true;
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
							canMove = true;
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
							canMove = true;
						}
					}
				}
			}
			break;

		default:
			break;
		}

		// ���͕����Ƀ^�C�����ړ��ł����ꍇ�͐V�����^�C�����X�|�[��
		if (canMove)
		{
			SpawnTile(direction);
		}
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
			// [0�`1)�̗����ɃO���b�h�̃T�C�Y��������0�`�O���b�h�̃T�C�Y�̗����𐶐�
			int x = floor(m_randomGenerator(m_randomEngine) * GRID_WIDTH);
			int y = floor(m_randomGenerator(m_randomEngine) * GRID_HEIGHT);
			if (m_grid[y][x] == 0)
			{
				int random = m_randomGenerator(m_randomEngine);
				if (random < 0.75f)
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
	void Grid::UpdateTile(float deltaTime)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				m_tiles[y][x]->Update(deltaTime);
				if (m_grid[y][x] != 0)
				{
					m_tiles[y][x]->GetComponent<Tile>()->SetNumber(m_grid[y][x]);
					m_tiles[y][x]->GetComponent<Tile>()->SetGridPosition(x, y, m_gridLeft, m_gridTop);
				}
			}
		}
	}
	bool Grid::CheckGameClear()
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				if (m_grid[y][x] == GAME_CLEAR_NUMBER)
				{
					return true;
				}
			}
		}
		return false;
	}
	// �󔒃}�X�����݂����A�����\�ȃ^�C�����Ȃ��ꍇ�̓Q�[���I�[�o�[
	bool Grid::CheckGameOver()
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				const unsigned int currentTile = m_grid[y][x];

				// �󔒃}�X�����邩�ǂ���
				if (currentTile == 0)
				{
					return false;
				}

				// �����\�ȃ^�C�������邩�ǂ���
				// �㑤�`�F�b�N
				if (y > 0 && m_grid[y - 1][x] == currentTile)
				{
					return false;
				}
				// �����`�F�b�N
				if (y < GRID_HEIGHT - 1 && m_grid[y + 1][x] == currentTile)
				{
					return false;
				}
				// �����`�F�b�N
				if (x > 0 && m_grid[y][x - 1] == currentTile)
				{
					return false;
				}
				// �E���`�F�b�N
				if (x < GRID_WIDTH - 1 && m_grid[y][x + 1] == currentTile)
				{
					return false;
				}
			}
		}

		// �󔒃}�X���Ȃ� ���� �����\�ȃ^�C�����Ȃ�
		return true;
	}
	void Grid::TileDraw()
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				if (m_grid[y][x] != 0)
				{
					m_tiles[y][x]->GetComponent<SpriteRenderer>()->Draw();
				}
			}
		}
	}
}
