#include "Component.h"

#include "GameObject.h"

void enf::Component::SetParent(GameObject* pParent)
{
	m_pParent = pParent;
}

void enf::Component::MarkForMurder()
{
	m_Delete = true;
}

void enf::Component::LetLive()
{
	m_Delete = false;
}

bool enf::Component::IsMarked() const
{
	return m_Delete;
}
