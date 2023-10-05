#include "pch.h"
#include "Tile.h"

#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/Transform2D.h"

namespace Game2048
{
	Tile::Tile(Framework::Object* owner, float width, float height) :
		Framework::IComponent(owner), m_width(width), m_height(height)
	{
		// Spriteコンポーネント追加
		auto sprite = m_owner->AddComponent<Framework::Sprite>(m_owner);
		sprite->LoadTexture(L"res/numberTile/Tile_2.png");
		auto transform = m_owner->GetComponent<Framework::Transform2D>();
		transform->scale = { m_width, m_height };
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
	void Tile::SetGridPosition(unsigned int x, unsigned int y, float gridTop, float gridLeft)
	{
		// 座標を設定
		auto transform = m_owner->GetComponent<Framework::Transform2D>();
		transform->position = { gridLeft + x * m_width, gridTop + y * m_height };
	}
	unsigned int Tile::GetNumber()
	{
		return m_number;
	}
}