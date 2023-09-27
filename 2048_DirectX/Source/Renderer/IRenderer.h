#pragma once

namespace Framework
{
	class Scene;
}

namespace RenderingEngine
{
	class IRenderer
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;
		virtual void Render(Framework::Scene& scene) = 0;
	};
}