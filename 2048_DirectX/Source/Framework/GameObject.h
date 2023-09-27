#pragma once
#include "Object.h"

namespace Framework
{
	class GameObject : public Object
	{
	public:
		GameObject() = default;
		~GameObject() = default;

	public:
		void Update(float deltaTime);
		void Draw();
	};
}