#pragma once
#include "Framework/IRenderer.h"

namespace Game2048
{
	class Renderer : public Framework::IRenderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		void Render(class Framework::Scene* scene) override;
	};
}