#include <cassert>

#include "Managers/InputManager.h"

#include "windows.h"
#include "Xinput.h"

#include "Action.h"
#include "InputMap.h"

class enf::InputManager::XInputImp final
{
public:
	XInputImp() = default;
	~XInputImp() = default;

	void ControllerInput(const Controller* controller, int controllerIndex)
	{
		CheckControllerState(controllerIndex);

		for (const auto& context : controller->GetInputMap()->GetControllerMap())
		{
			switch (context.first->GetControllerInputState())
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
				default:
					assert(false && "Controller state not support");
			}
		}
	}

private:
	XINPUT_STATE m_CurrentState{};
	int m_ButtonsPressed{};
	int m_ButtonsReleased{};

	void CheckControllerState(DWORD controllerIndex)
	{
		XINPUT_STATE previousState;
		CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(controllerIndex, &m_CurrentState);

		const int buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		m_ButtonsPressed = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleased = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	[[nodiscard]] bool IsTriggered(unsigned int button) const
	{
		return m_ButtonsPressed & button;
	}

	[[nodiscard]] bool IsReleased(unsigned int button) const
	{
		return m_ButtonsReleased & button;
	}

	[[nodiscard]] bool IsDown(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	WORD EngineButtonToXInput(Action::ControllerLayout button)
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
			assert(false && "Controller input not support");
			return 0;
		}
	}
};

void enf::InputManager::HandleControllerEvent()
{
	int controllerIndex{};
	for (auto&& controller : m_Controllers)
	{
		m_ControllerImplPtr->ControllerInput(controller.get(), controllerIndex);

		++controllerIndex;
	}
}

enf::InputManager::InputManager() :
	m_ControllerImplPtr(std::make_unique<XInputImp>())
{
}

enf::InputManager::~InputManager() = default;