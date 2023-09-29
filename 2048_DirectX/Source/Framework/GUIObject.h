#pragma once
#include "Object.h"

namespace Framework
{
	class GUIObject : public Object
	{
	public:
		GUIObject() = default;
		~GUIObject() = default;

	public:
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}