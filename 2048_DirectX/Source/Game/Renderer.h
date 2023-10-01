#pragma once
#include <d3d12.h>

#include "Framework/IRenderer.h"
#include "Utility/EngineUtility.h"

namespace DX12Wrapper
{
	class RootSignature;
	class GraphicsPipelineState;
}

namespace Game2048
{
	class Renderer : public Framework::IRenderer
	{
	public:
		Renderer();
		~Renderer();
	
	private:
		std::unique_ptr<DX12Wrapper::RootSignature> m_rootSignature;
		std::unique_ptr<DX12Wrapper::GraphicsPipelineState> m_pipelineState;
	
		Utility::RESULT CreateGraphicsPipelineState(ID3D12Device& device);
		Utility::RESULT CreateRootSignature(ID3D12Device& device);

	public:
		Utility::RESULT Init() override;
		void Render(std::vector<std::unique_ptr<Framework::Object>>& gameObjects) override;
	};
}