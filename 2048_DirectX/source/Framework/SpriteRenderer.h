#pragma once
#include "IComponent.h"

#include "DX12Wrapper/RootSignature.h"
#include "DX12Wrapper/GraphicsPipelineState.h"

#include <DirectXMath.h>

namespace Framework
{
	class SpriteRenderer : public IComponent
	{
	public:
		SpriteRenderer(Framework::Object* owner, class Sprite* sprite);
		~SpriteRenderer() = default;

		void SetSprite(class Sprite* sprite);
		void Update(float deltaTime) override;
		void Draw() override;

		Utility::RESULT CreateGraphicsPipelineState(ID3D12Device& device);
		Utility::RESULT CreateRootSignature(ID3D12Device& device);

	private:
		std::unique_ptr<DX12Wrapper::RootSignature> m_rootSignature = nullptr;
		std::unique_ptr<DX12Wrapper::GraphicsPipelineState> m_pipelineState = nullptr;
		std::unique_ptr<class Sprite> m_sprite = nullptr;
	};
}