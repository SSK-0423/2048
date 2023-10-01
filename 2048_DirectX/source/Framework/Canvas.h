#pragma once

namespace Framework
{
	class Canvas
	{
	public:
		Canvas() = default;
		virtual ~Canvas() {};

		virtual void Update(float deltaTime);
		virtual void Draw();
	};
}