#pragma once
#include "Component.h"

namespace Framework
{
	class Transform : public Component
	{
	public:
		Transform(Object& owner) : Component(owner)
		{

		}
		~Transform() = default;
	private:
		// ConstantBuffer

		// DirectXMathŒn‚Ìˆ—
	};
}