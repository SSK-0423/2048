#pragma once
#include <memory>

namespace Framework
{
	class Object;

	class Component
	{
	public:
		Component(Object& owner) : owner(owner) {};
		~Component() = default;

	private:
		Object& owner;
	};
}