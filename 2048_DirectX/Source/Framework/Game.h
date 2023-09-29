#pragma once
#include "Window.h"

namespace Framework
{
	/// <summary>
	/// �Q�[���S�̂��Ǘ�����N���X
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

		// �����_���[
		
		// �V�[��
	};
}