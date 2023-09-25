#pragma once
#include "Window.h"

namespace GameFramework
{
	/// <summary>
	/// ゲーム全体を管理するクラス
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