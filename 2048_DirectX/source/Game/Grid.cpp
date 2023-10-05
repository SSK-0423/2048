#include "pch.h"
#include "Grid.h"
#include "Tile.h"

#include "Framework/Window.h"
#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/Transform2D.h"
#include "Framework/InputSystem.h"

constexpr size_t GRID_WIDTH = 4;
constexpr size_t GRID_HEIGHT = 4;

using namespace Framework;

namespace Game2048
{
	Grid::Grid(Framework::Object* owner) : IComponent(owner)
	{
		// Sprite�R���|�[�l���g�ǉ�
		auto sprite = m_owner->AddComponent<Sprite>(m_owner);
		sprite->LoadTexture(L"res/Grid.png");

		auto windowSize = Window::GetWindowSize();

		auto transform = m_owner->GetComponent<Transform2D>();
		transform->scale = { 300, 300 };
		transform->position = { windowSize.cx / 2.f, windowSize.cy / 2.f };

		// �O���b�h�̍�����W�擾
		m_gridLeft = transform->position.x - transform->scale.x;
		m_gridTop = transform->position.y - transform->scale.y;

		// �O���b�h�̏�����
		m_grid.resize(GRID_HEIGHT);
		std::for_each(m_grid.begin(), m_grid.end(), [](auto& row) { row.resize(GRID_WIDTH); });

		// �p�l���̏�����
		int tileWidth = transform->scale.x / GRID_WIDTH;
		int tileHeight = transform->scale.y / GRID_HEIGHT;

		m_testTile = std::make_unique<GameObject>();
		m_testTile->AddComponent<Tile>(m_testTile.get(), tileWidth, tileHeight);

		m_owner->AddChild(m_testTile.get());
	}

	void Grid::Update(float deltaTime)
	{
		// �O���b�h�̍X�V
		auto& input = InputSystem::Instance();

		m_testTile->GetComponent<Tile>()->SetGridPosition(0, 0, m_gridLeft, m_gridTop);
	}
	void Grid::Draw()
	{}
}
