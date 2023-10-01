#pragma once
#include "IComponent.h"
/// <summary>
/// ŽÀ‘••û–@
/// 1. Canvas‚ÉAdd
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