#include "Component.h"

#include "GameObject.h"

void enf::Component::SetParent(GameObject* pParent)
{
	m_pParent = std::shared_ptr<GameObject>(pParent);
}
