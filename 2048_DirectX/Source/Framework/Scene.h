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

		virtual void Init() = 0;
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
		virtual void Final() = 0;


		const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;
		const std::vector<std::unique_ptr<Canvas>>& GetCanvases() const;

		void SetActive(bool isActive);

		static const class Camera& GetCamera()
		{
			return *m_camera.get();
		}
	protected:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		std::vector<std::unique_ptr<Canvas>> m_canvases;

		// ƒV[ƒ“‚²‚Æ‚ÉInitŠÖ”‚Å‰Šú‰»‚·‚é
		static std::unique_ptr<class Camera> m_camera;

		bool m_isActive = false;
	};
}