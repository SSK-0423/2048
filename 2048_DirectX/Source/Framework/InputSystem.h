#pragma once

namespace Framework
{
	class InputSystem
	{
	private:
		InputSystem() = default;
		~InputSystem() = default;

	public:
		void Update();

		bool GetKeyDown();

		bool GetKeyUp();

		static InputSystem& Instance() {
			static InputSystem inst;
			return inst;
		}
	};
}