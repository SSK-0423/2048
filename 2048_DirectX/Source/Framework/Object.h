#pragma once
#include "IComponent.h"
#include "Transform2D.h"

namespace Framework
{
	class Object
	{
	public:
		Object() { m_components.push_back(std::make_unique<Transform2D>(this)); }
		virtual ~Object()
		{
			m_components.clear();
			m_components.shrink_to_fit();
		}

	protected:
		std::vector<std::unique_ptr<IComponent>> m_components;

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
	};
}