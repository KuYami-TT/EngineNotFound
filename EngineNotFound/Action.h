#pragma once
#include "SDL_keycode.h"

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

		enum class KeyboardLayout
		{
			KEYBOARD_Q,
			KEYBOARD_W,
			KEYBOARD_E,
			KEYBOARD_R,
			KEYBOARD_T,
			KEYBOARD_Y,
			KEYBOARD_U,
			KEYBOARD_I,
			KEYBOARD_O,
			KEYBOARD_P,
			KEYBOARD_A,
			KEYBOARD_S,
			KEYBOARD_D,
			KEYBOARD_F,
			KEYBOARD_G,
			KEYBOARD_H,
			KEYBOARD_J,
			KEYBOARD_K,
			KEYBOARD_L,
			KEYBOARD_Z,
			KEYBOARD_X,
			KEYBOARD_C,
			KEYBOARD_V,
			KEYBOARD_B,
			KEYBOARD_N,
			KEYBOARD_M,

			KEYBOARD_1,
			KEYBOARD_2,
			KEYBOARD_3,
			KEYBOARD_4,
			KEYBOARD_5,
			KEYBOARD_6,
			KEYBOARD_7,
			KEYBOARD_8,
			KEYBOARD_9,
			KEYBOARD_0,

			KEYBOARD_RETURN,
			KEYBOARD_ESCAPE,
			KEYBOARD_BACKSPACE,
			KEYBOARD_TAB,
			KEYBOARD_SPACE
		};

		Action(InputState inputState, ControllerLayout controllerInput);
		Action(InputState inputState, KeyboardLayout keyboardInput);
		~Action() = default;

		Action(Action&& other) = delete;
		Action(const Action& other) = delete;
		Action& operator=(Action&& other) = delete;
		Action& operator=(const Action& other) = delete;

		[[nodiscard]] InputState GetInputState() const;
		[[nodiscard]] ControllerLayout GetControllerInput() const;
		[[nodiscard]] KeyboardLayout GetKeyboardInput() const;

	private:
		InputState m_InputState;
		ControllerLayout m_ControllerInput;
		KeyboardLayout m_KeyBoardInput;
	};
}
