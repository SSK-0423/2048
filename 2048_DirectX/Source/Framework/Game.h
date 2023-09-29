#pragma once
#include "Window.h"

namespace Framework
{
	/// <summary>
	/// ゲーム全体を管理するクラス
	/// </summary>
	class Game
	{
	private:
		Game() = default;
		~Game() = default;

	public:

		void Init();

		void Run();

		void Final();

		static Game& Instance() {
			static Game inst;
			return inst;
		}
	private:
		Window m_window;
		std::chrono::system_clock::time_point m_prevFrameTime;

		// レンダラー
		
		// シーン
	};
}