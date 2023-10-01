#include "pch.h"
#include "Object.h"
#include "Transform2D.h"

namespace Framework
{
	Object::Object()
	{
		m_components.push_back(std::make_unique<Transform2D>(this));
	}
}