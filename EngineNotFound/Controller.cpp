#include "Controller.h"

#include "XInputImp.h"

enf::Controller::Controller(GameObject* possessed, InputMap* inputMap, int controllerIndex) :
	m_ControllerImplPtr{ new XInputImp() },
	m_Possessed{ possessed },
	m_InputMap{ inputMap },
	m_ControllerIndex{ controllerIndex }
{
}

void enf::Controller::HandleControllerInput()
{
	m_ControllerImplPtr->HandleControllerInput(this, m_ControllerIndex);
}

enf::GameObject* enf::Controller::GetPossessed() const
{
	return m_Possessed;
}

enf::InputMap* enf::Controller::GetInputMap() const
{
	return m_InputMap;
}
