#pragma once
#include "Window.h"

namespace GameFramework
{
	/// <summary>
	/// �Q�[���S�̂��Ǘ�����N���X
	/// </summary>
	class Game
	{
	private:
		Game() = default;

	public:
		~Game() = default;

		void Init();

		void Run();

		void Final();

		static Game& Instance() {
			static Game inst;
			return inst;
		}
	private:
		Window m_window;
	};
}