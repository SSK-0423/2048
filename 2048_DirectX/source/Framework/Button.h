#pragma once
#include "IComponent.h"
/// <summary>
/// �������@
/// 1. Canvas��Add
/// 
/// </summary>

namespace Framework
{
	class Button : public IComponent
	{
	public:
		Button();
		~Button();

	private:
		void Update(float deltaTime) override;
		void Draw() override;
	};
}