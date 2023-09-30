#pragma once
#include "IComponent.h"
#include "Utility/EngineUtility.h"

#include <DirectXMath.h>

namespace DX12Wrapper
{
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class DescriptorHeapCBV_SRV_UAV;
}

namespace Framework
{
	class Sprite : public IComponent
	{
	public:
		Sprite(Object* owner);
		~Sprite() = default;

	private:
		struct SpriteVertex
		{
			DirectX::XMFLOAT3 vertex;
			DirectX::XMFLOAT2 uv;
		};
		std::vector<SpriteVertex> m_vertex;

		std::unique_ptr<DX12Wrapper::Texture> m_texture;
		std::unique_ptr<DX12Wrapper::VertexBuffer> m_vertexBuffer;
		std::unique_ptr<DX12Wrapper::IndexBuffer> m_indexBuffer;
		std::unique_ptr<DX12Wrapper::DescriptorHeapCBV_SRV_UAV> m_descriptorHeap;

	public:
		void LoadTexture(const std::wstring& path);
		void Update(float deltaTime) override;
		void Draw() override;
	};
}