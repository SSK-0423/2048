#include "pch.h"
#include "Tile.h"
#include "GameScene.h"

#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/SpriteRenderer.h"
#include "Framework/Transform2D.h"
#include "Framework/Window.h"

using namespace Framework;

constexpr float TILE_OFFSET = 0.f;

namespace Game2048
{
	Tile::Tile(Framework::Object* owner) :IComponent(owner)
	{
		// SpriteRendererコンポーネント追加
		auto spriteRenderer = m_owner->AddComponent<SpriteRenderer>(m_owner);
		spriteRenderer->SetSprite(new Sprite(L"res/numberTile/tile_2.png", SPRITE_PIVOT::TOP_LEFT));
		spriteRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::TILE));
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
	void Tile::SetScale(float width, float height)
	{
		m_width = width;
		m_height = height;
		m_owner->GetComponent<Transform2D>()->scale = { m_width, m_height };
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