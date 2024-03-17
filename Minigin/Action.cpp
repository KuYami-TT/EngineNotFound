#include "Action.h"

enf::Action::Action(InputState inputState, ControllerLayout input) :
	m_InputState{inputState},
	m_Input{input}
{
}

enf::Action::InputState enf::Action::GetInputState() const
{
	return m_InputState;
}

enf::Action::ControllerLayout enf::Action::GetInput() const
{
	return m_Input;
}
