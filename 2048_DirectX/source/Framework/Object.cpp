#include "pch.h"
#include "Object.h"
#include "Transform2D.h"

namespace Framework
{
	Object::Object() : m_parent(nullptr), m_children()
	{
		m_components.push_back(std::make_unique<Transform2D>(this));
	}
	Object* Object::Parent()
	{
		return m_parent;
	}
	void Object::SetParent(Object* parent)
	{
		m_parent = parent;
	}
	void Object::AddChild(Object* child)
	{
		m_children.push_back(child);
	}
}