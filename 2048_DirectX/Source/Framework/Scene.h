#pragma once
#include "Object.h"
#include "Canvas.h"

namespace Framework
{
	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;

	protected:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		std::vector<std::unique_ptr<Canvas>> m_canvases;
	public:
		virtual void Init() = 0;
		virtual void Update(float deltaTime);
		virtual void DrawScene(class IRenderer& renderer);
		virtual void DrawUI();
		virtual void Final() = 0;

		std::vector<std::unique_ptr<GameObject>>& GetGameObjects()
		{
			return m_gameObjects;
		}
	};
}