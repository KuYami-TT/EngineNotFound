#include <cassert>

#include "Managers/InputManager.h"
#include "XInputImp.h"
#include "InputMap.h"

void enf::XInputImp::HandleControllerInput(const Controller* controller, int controllerIndex)
{
	CheckControllerState(controllerIndex);

	for (auto&& context : controller->GetInputMap()->GetControllerMap())
	{
		switch (context.first->GetInputState())
		{
		case Action::InputState::OnTrigger:
		{
			if (IsTriggered(EngineButtonToXInput(context.first->GetControllerInput())))
			{
				context.second->Execute();
			}
			break;
		}
		case Action::InputState::OnRelease:
		{
			if (IsReleased(EngineButtonToXInput(context.first->GetControllerInput())))
			{
				context.second->Execute();
			}
			break;
		}
		case Action::InputState::OnDown:
		{
			if (IsDown(EngineButtonToXInput(context.first->GetControllerInput())))
			{
				context.second->Execute();
			}
			break;
		}
		}
	}
}

bool enf::XInputImp::IsTriggered(unsigned button) const
{
	return m_ButtonsTriggered & button;
}

bool enf::XInputImp::IsReleased(unsigned button) const
{
	return m_ButtonsReleased & button;
}

bool enf::XInputImp::IsDown(unsigned button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

WORD enf::XInputImp::EngineButtonToXInput(Action::ControllerLayout button)
{
	switch (button)
	{
	case Action::ControllerLayout::GAMEPAD_DPAD_UP:			return XINPUT_GAMEPAD_DPAD_UP;
	case Action::ControllerLayout::GAMEPAD_DPAD_DOWN:		return XINPUT_GAMEPAD_DPAD_DOWN;
	case Action::ControllerLayout::GAMEPAD_DPAD_LEFT:		return XINPUT_GAMEPAD_DPAD_LEFT;
	case Action::ControllerLayout::GAMEPAD_DPAD_RIGHT:		return XINPUT_GAMEPAD_DPAD_RIGHT;
	case Action::ControllerLayout::GAMEPAD_START:			return XINPUT_GAMEPAD_START;
	case Action::ControllerLayout::GAMEPAD_BACK:			return XINPUT_GAMEPAD_BACK;
	case Action::ControllerLayout::GAMEPAD_LEFT_THUMB:		return XINPUT_GAMEPAD_LEFT_THUMB;
	case Action::ControllerLayout::GAMEPAD_RIGHT_THUMB:		return XINPUT_GAMEPAD_RIGHT_THUMB;
	case Action::ControllerLayout::GAMEPAD_LEFT_SHOULDER:	return XINPUT_GAMEPAD_LEFT_SHOULDER;
	case Action::ControllerLayout::GAMEPAD_RIGHT_SHOULDER:	return XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case Action::ControllerLayout::GAMEPAD_A:				return XINPUT_GAMEPAD_A;
	case Action::ControllerLayout::GAMEPAD_B:				return XINPUT_GAMEPAD_B;
	case Action::ControllerLayout::GAMEPAD_X:				return XINPUT_GAMEPAD_X;
	case Action::ControllerLayout::GAMEPAD_Y:				return XINPUT_GAMEPAD_Y;
	default:
		assert(false && "No button support");
		return 0;
	}
}

void enf::XInputImp::CheckControllerState(DWORD controllerIndex)
{
	XINPUT_STATE previousState{};
	CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(controllerIndex, &m_CurrentState);

	const int buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	m_ButtonsTriggered = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleased = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}
