#include "pch.h"
#include "Grid.h"

#include "Framework/Window.h"
#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/Transform2D.h"

constexpr size_t GRID_WIDTH = 4;
constexpr size_t GRID_HEIGHT = 4;

using namespace Framework;

namespace Game2048
{
	Grid::Grid(Framework::Object* owner) : IComponent(owner)
	{
		// Spriteコンポーネント追加
		auto sprite = m_owner->AddComponent<Sprite>(m_owner);
		sprite->LoadTexture(L"res/Grid.png");

		auto windowSize = Window::GetWindowSize();

		auto transform = m_owner->GetComponent<Transform2D>();
		transform->scale = { 300, 300 };
		transform->position = { windowSize.cx / 2.f, windowSize.cy / 2.f };

		// グリッドの初期化
		m_grid.resize(GRID_HEIGHT);
		std::for_each(m_grid.begin(), m_grid.end(), [](auto& row) { row.resize(GRID_WIDTH); });
	}
	void Grid::Update(float deltaTime)
	{
	}
	void Grid::Draw()
	{
	}
}
