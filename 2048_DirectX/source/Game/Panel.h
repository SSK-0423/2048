#pragma once
#include "Framework/IComponent.h"

namespace Game2048
{
	class Panel : public Framework::IComponent
	{
	public:
		Panel(Framework::Object* owner);
		~Panel() = default;

		void Init();
		void Final();
	};
}