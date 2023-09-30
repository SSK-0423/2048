#pragma once

namespace Framework
{
	class IRenderer
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;
		virtual void Render(class Scene* scene) = 0;
	};
}