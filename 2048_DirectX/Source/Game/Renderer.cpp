#include "pch.h"

#include "Renderer.h"
#include "DX12Wrapper/Dx12GraphicsEngine.h"

namespace Game2048
{
	void Renderer::Render(Framework::Scene* scene)
	{
		auto& graphicsEngine = DX12Wrapper::Dx12GraphicsEngine::Instance();

		graphicsEngine.BeginDraw();
		{

		}
		graphicsEngine.EndDraw();
	}
}

