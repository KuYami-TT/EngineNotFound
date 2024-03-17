#pragma once

namespace enf
{
	class Action final
	{
	public:
		enum class InputState
		{
			OnTrigger,
			OnRelease,
			OnDown
		};

		enum class ControllerLayout
		{
			ZERO,
			GAMEPAD_DPAD_UP,
			GAMEPAD_DPAD_DOWN,
			GAMEPAD_DPAD_LEFT,
			GAMEPAD_DPAD_RIGHT,
			GAMEPAD_START,
			GAMEPAD_BACK,
			GAMEPAD_LEFT_THUMB,
			GAMEPAD_RIGHT_THUMB,
			GAMEPAD_LEFT_SHOULDER,
			GAMEPAD_RIGHT_SHOULDER,
			GAMEPAD_A,
			GAMEPAD_B,
			GAMEPAD_X,
			GAMEPAD_Y
		};

		Action(InputState inputState, ControllerLayout input);
		~Action() = default;

		Action(Action&& other) = delete;
		Action(const Action& other) = delete;
		Action& operator=(Action&& other) = delete;
		Action& operator=(const Action& other) = delete;

		[[nodiscard]] InputState GetInputState() const;
		[[nodiscard]] ControllerLayout GetInput() const;

	private:
		InputState m_InputState;
		ControllerLayout m_Input;
	};
}