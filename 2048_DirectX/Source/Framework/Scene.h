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

		bool m_isActive = false;
	public:
		virtual void Init() = 0;
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
		virtual void Final() = 0;

		const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;
		const std::vector<std::unique_ptr<Canvas>>& GetCanvases() const;

		void SetActive(bool isActive);
	};
}