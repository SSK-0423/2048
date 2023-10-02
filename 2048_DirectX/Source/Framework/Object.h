#pragma once
#include "IComponent.h"

namespace Framework
{
	class Object
	{
	public:
		Object();
		virtual ~Object()
		{
			m_components.clear();
			m_components.shrink_to_fit();
		}

	protected:
		std::vector<std::unique_ptr<IComponent>> m_components;
		Object* m_parent;
		std::vector<Object*> m_children;

	public:
		template<class T>
		T* GetComponent()
		{
			for (auto& comp : m_components)
			{
				if (typeid(*comp.get()) == typeid(T))
					return static_cast<T*>(comp.get());
			}

			return nullptr;
		}

		template<class T, class ...K>
		T* AddComponent(K ...k)
		{
			for (auto& comp : m_components) {
				if (typeid(*comp.get()) == typeid(T))
					return nullptr;
			}
			auto component = std::make_unique<T>(k...);
			m_components.push_back(std::move(component));

			return static_cast<T*>(m_components[m_components.size() - 1].get());
		}

		void Update(float deltaTime);
		void Draw();

		Object* Parent();
		void SetParent(Object* parent);
		void AddChild(Object* child);
	};

	// Object‚É•Ê–¼‚ð‚Â‚¯‚é
	using GameObject = Object;
	using GUIObject = Object;
}