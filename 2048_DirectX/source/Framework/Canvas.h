#pragma once
#include "Object.h"

namespace Framework
{
	class Canvas
	{
	public:
		Canvas() = default;
		virtual ~Canvas() {};

		virtual void Update(float deltaTime);
		virtual void Draw();

	private:
		std::vector<std::unique_ptr<Object>> m_guiObjects;
	};
}