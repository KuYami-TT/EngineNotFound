#include "Action.h"

enf::Action::Action(InputState inputState, ControllerLayout controllerInput) :
	m_InputState{ inputState },
	m_ControllerInput{ controllerInput }
{
}

enf::Action::Action(InputState inputState, KeyboardLayout keyboardInput) :
	m_InputState{ inputState },
	m_KeyBoardInput{ keyboardInput }
{
}

enf::Action::InputState enf::Action::GetInputState() const
{
	return m_InputState;
}

enf::Action::ControllerLayout enf::Action::GetControllerInput() const
{
	return m_ControllerInput;
}

enf::Action::KeyboardLayout enf::Action::GetKeyboardInput() const
{
	return m_KeyBoardInput;
}
