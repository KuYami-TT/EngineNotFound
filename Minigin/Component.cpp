#include "Component.h"

#include "GameObject.h"

void enf::Component::SetParent(GameObject* pParent)
{
	m_pParent = pParent;
}
