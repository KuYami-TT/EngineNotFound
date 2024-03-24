#include "Controller.h"

enf::Controller::Controller(GameObject* possessed, InputMap* inputMap) :
	m_Possessed{ possessed },
	m_InputMap{ inputMap }
{
}

enf::GameObject* enf::Controller::GetPossessed() const
{
	return m_Possessed;
}

enf::InputMap* enf::Controller::GetInputMap() const
{
	return m_InputMap;
}
