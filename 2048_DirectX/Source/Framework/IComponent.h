#pragma once

namespace Framework
{
	class Object;

	class IComponent
	{
	public:
		IComponent(Object& owner) : owner(owner) {};
		virtual ~IComponent() = default;

	private:
		Object& owner;

	public:
		virtual void Update(float deltaTime) = 0;
	};
}