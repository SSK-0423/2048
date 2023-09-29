#pragma once
#include "GameObject.h"
#include "GUIObject.h"

namespace Framework
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

	protected:
		std::vector<GameObject> m_gameObjects;
		std::vector<GUIObject> m_guiObjects;

	public:
		virtual void Init() = 0;
		void Update(float deltaTime);
		void Draw();
		virtual void Final() = 0;
	};
}