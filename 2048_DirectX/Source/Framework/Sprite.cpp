#include "Sprite.h"
#include "Utility/EngineUtility.h"

using namespace Utility;

namespace Framework
{
	void Sprite::Render()
	{
	}
	void Sprite::LoadTexture(const std::wstring& path)
	{
		RESULT result = texture.CreateTextureFromWIC(DX12Wrapper::Dx12GraphicsEngine::Instance(), path);
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "テクスチャ読み込みに失敗しました。", "エラー", MB_OK);
		}
	}
	void Sprite::Update(float deltaTime)
	{
	}
	void Sprite::Draw()
	{
	}
}