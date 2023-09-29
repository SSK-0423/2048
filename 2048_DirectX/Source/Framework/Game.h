#pragma once
#include "Window.h"
#include "GameImpl.h"

namespace Framework
{
	/// <summary>
	/// ゲーム全体を管理するクラス
	/// </summary>
	class Game
	{
	private:
		Game(GameImpl& gameImpl) : m_gameImpl(gameImpl) {};
		~Game() = default;

	public:

		void Init();

		void Run();

		void Final();

		static Game& Instance(GameImpl& gameImpl) {
			static Game inst(gameImpl);
			return inst;
		}
	private:
		Window m_window;
		std::chrono::system_clock::time_point m_prevFrameTime;
		GameImpl& m_gameImpl;
	};
}