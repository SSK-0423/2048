#pragma once
#include <vector>
#include <memory>
#include "IComponent.h"

namespace Framework
{
	class Object
	{
	public:
		Object() = default;
		~Object()
		{
			m_components.clear();
			m_components.shrink_to_fit();
		}

	private:
		std::vector<std::unique_ptr<IComponent>> m_components;

	public:
		template<class T>
		T* GetComponent()
		{
		}
		template<class T, class ...K>
		T* AddComponent(K ...k)
		{
		}
	};
}