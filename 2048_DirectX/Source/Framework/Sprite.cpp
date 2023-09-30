#include "Sprite.h"
#include "Utility/EngineUtility.h"

#include "DX12Wrapper/VertexBuffer.h"
#include "DX12Wrapper/IndexBuffer.h"
#include "DX12Wrapper/GraphicsPipelineState.h"
#include "DX12Wrapper/RootSignature.h"
#include "DX12Wrapper/DescriptorHeapCBV_SRV_UAV.h"
#include "DX12Wrapper/Texture.h"
#include "DX12Wrapper/ShaderResourceViewDesc.h"

#include "DX12Wrapper/RenderingContext.h"

using namespace Utility;
using namespace DX12Wrapper;

namespace Framework
{
	Sprite::Sprite(Object* owner)
		: IComponent(owner),
		m_texture(std::make_unique<Texture>()),
		m_vertexBuffer(std::make_unique<VertexBuffer>()),
		m_indexBuffer(std::make_unique<IndexBuffer>()),
		m_descriptorHeap(std::make_unique<DescriptorHeapCBV_SRV_UAV>())
	{
		m_vertex.push_back({ DirectX::XMFLOAT3(-0.5f, -0.5f, 0),DirectX::XMFLOAT2(0, 1) });
		m_vertex.push_back({ DirectX::XMFLOAT3(-0.5f,  0.5f, 0),DirectX::XMFLOAT2(0, 0) });
		m_vertex.push_back({ DirectX::XMFLOAT3( 0.5f, -0.5f, 0),DirectX::XMFLOAT2(1, 1) });
		m_vertex.push_back({ DirectX::XMFLOAT3( 0.5f,  0.5f, 0),DirectX::XMFLOAT2(1, 0) });

		ID3D12Device& device = Dx12GraphicsEngine::Instance().Device();

		RESULT result = m_vertexBuffer->Create(device, &m_vertex[0], SizeofVector<SpriteVertex>(m_vertex), sizeof(SpriteVertex));
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "VertexBufferの生成に失敗", "エラー", MB_OK);
		}
		result = m_indexBuffer->Create(device, { 0,1,2,2,1,3 });
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "IndexBufferの生成に失敗", "エラー", MB_OK);
		}
		result = m_descriptorHeap->Create(device);
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "DescriptorHeapの生成に失敗", "エラー", MB_OK);
		}
	}

	void Sprite::LoadTexture(const std::wstring& path)
	{
		RESULT result = m_texture->CreateTextureFromWIC(Dx12GraphicsEngine::Instance(), path);
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "テクスチャ読み込みに失敗しました。", "エラー", MB_OK);
		}

		ID3D12Device& device = Dx12GraphicsEngine::Instance().Device();
		ShaderResourceViewDesc desc(*m_texture);
		m_descriptorHeap->RegistShaderResource(device, *m_texture, desc);
	}
	void Sprite::Update(float deltaTime)
	{
	}
	void Sprite::Draw()
	{
		DX12Wrapper::RenderingContext renderingContext = DX12Wrapper::Dx12GraphicsEngine::Instance().GetRenderingContext();

		renderingContext.SetDescriptorHeap(*m_descriptorHeap);
		renderingContext.SetVertexBuffer(0, *m_vertexBuffer);
		renderingContext.SetIndexBuffer(*m_indexBuffer);
		renderingContext.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		renderingContext.DrawIndexedInstanced(m_indexBuffer->GetIndexNum(), 1);
	}
}