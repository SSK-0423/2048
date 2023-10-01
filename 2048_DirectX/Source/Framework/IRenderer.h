#pragma once

#include "Utility/EngineUtility.h"

namespace Framework
{
	class IRenderer
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;
		virtual Utility::RESULT Init() = 0;
		virtual void Render(std::vector<std::unique_ptr<class Object>>& gameObjects) = 0;
	};
}