#pragma once
#include "IComponent.h"

namespace Framework
{
	class Transform : public IComponent
	{
	public:
		Transform(Object& owner) : IComponent(owner)
		{

		}
		~Transform() = default;
	private:
		// ConstantBuffer

		// DirectXMathŒn‚Ìˆ—
	};
}