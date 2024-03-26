#pragma once
#include "windows.h"
#include "Xinput.h"

#include "Action.h"

namespace enf
{
	class Controller;

	class XInputImp final
	{
	public:
		XInputImp() = default;
		~XInputImp() = default;

		void HandleControllerInput(const Controller* controller, int controllerIndex);

	private:
		XINPUT_STATE m_CurrentState{};
		int m_ButtonsTriggered{};
		int m_ButtonsReleased{};

		void CheckControllerState(DWORD controllerIndex);

		[[nodiscard]] bool IsTriggered(unsigned int button) const;
		[[nodiscard]] bool IsReleased(unsigned int button) const;
		[[nodiscard]] bool IsDown(unsigned int button) const;

		WORD EngineButtonToXInput(Action::ControllerLayout button);
	};
}
