#pragma once

namespace Framework
{
	class Object;

	class IComponent
	{
	public:
		IComponent(Object* owner) : owner(owner) {};
		virtual ~IComponent() { OutputDebugStringA("IComponent Destructor"); };

	private:
		Object* owner;

	public:
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;
	};
}