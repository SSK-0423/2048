#include "pch.h"
#include "Tile.h"

#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/Transform2D.h"
#include "Framework/Window.h"

using namespace Framework;

constexpr float TILE_OFFSET = 0.f;

namespace Game2048
{
	Tile::Tile(Framework::Object* owner, float width, float height) :
		IComponent(owner), m_width(width), m_height(height)
	{
		// Spriteコンポーネント追加
		auto sprite = m_owner->AddComponent<Sprite>(m_owner, SPRITE_PIVOT::TOP_LEFT);
		sprite->LoadTexture(L"res/numberTile/Tile_2.png");

		// ウインドウサイズ取得
		auto window = Window::GetWindowSize();
		auto transform = m_owner->GetComponent<Transform2D>();
		transform->scale = { m_width, m_height };
		transform->position = { window.cx / 2.f, window.cy / 2.f };
	}
	void Tile::Update(float deltaTime)
	{
	}
	void Tile::Draw()
	{
	}
	void Tile::SetNumber(unsigned int number)
	{
		m_number = number;
	}
	void Tile::SetGridPosition(unsigned int x, unsigned int y, float gridLeft, float gridTop)
	{
		// 座標を設定
		auto transform = m_owner->GetComponent<Transform2D>();
		transform->position = {
			gridLeft + x * m_width + TILE_OFFSET * (x + 1),
			gridTop + y * m_height + TILE_OFFSET * (y + 1) };
	}
	unsigned int Tile::GetNumber()
	{
		return m_number;
	}
}