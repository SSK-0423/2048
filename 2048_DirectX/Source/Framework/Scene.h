#pragma once
#include "GameObject.h"
#include "GUIObject.h"

namespace Framework
{
	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;

	protected:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		std::vector<std::unique_ptr<GUIObject>> m_guiObjects;

	public:
		virtual void Init() = 0;
		void Update(float deltaTime);
		virtual void Final() = 0;

		std::vector<std::unique_ptr<GameObject>>& GetGameObjects()
		{
			return m_gameObjects;
		}
	};
}