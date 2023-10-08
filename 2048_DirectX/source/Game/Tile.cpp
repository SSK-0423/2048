#include "pch.h"
#include "Tile.h"
#include "GameScene.h"

#include "Framework/Object.h"
#include "Framework/Sprite.h"
#include "Framework/SpriteRenderer.h"
#include "Framework/Transform2D.h"
#include "Framework/Text.h"
#include "Framework/Window.h"

#include "DX12Wrapper/Texture.h"

using namespace Framework;
using namespace DX12Wrapper;
using namespace Utility;

constexpr float TILE_OFFSET = 0.f;

namespace Game2048
{
	std::unordered_map<unsigned int, std::shared_ptr<Texture>> Tile::m_tileTextures;

	Tile::Tile(Framework::Object* owner) :IComponent(owner)
	{
		// SpriteRendererコンポーネント追加
		auto spriteRenderer = m_owner->AddComponent<SpriteRenderer>(m_owner);
		spriteRenderer->SetSprite(new Sprite(L"", SPRITE_PIVOT::TOP_LEFT));
		spriteRenderer->SetLayer(static_cast<UINT>(GameScene::DRAW_LAYER::TILE));
	}
	void Tile::Update(float deltaTime)
	{
	}
	void Tile::Draw()
	{
	}
	void Tile::LoadTileTextures()
	{
		// テクスチャ読み込み
		for (int i = 2; i <= 2048; i *= 2)
		{
			std::wstring path = L"res/numberTile/tile_" + std::to_wstring(i) + L".png";

			m_tileTextures[i] = std::make_shared<Texture>();
			RESULT result = m_tileTextures[i]->CreateTextureFromWIC(Dx12GraphicsEngine::Instance(), path);
			if (result == RESULT::FAILED)
			{
				MessageBoxA(NULL, "テクスチャの読み込みに失敗", "エラー", MB_OK);
			}
		}
	}
	void Tile::SetNumber(unsigned int number)
	{
		if (m_number != number)
		{
			m_number = number;
			// 数字に応じたテクスチャ読み込み
			m_owner->GetComponent<SpriteRenderer>();
			auto sprite = new Sprite(L"", SPRITE_PIVOT::TOP_LEFT);
			sprite->SetTexture(m_tileTextures[m_number]);
			m_owner->GetComponent<SpriteRenderer>()->SetSprite(sprite);
		}
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