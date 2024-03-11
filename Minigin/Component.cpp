#include "Component.h"

void enf::Component::SetOwner(GameObject* ownerPtr)
{
	m_OwnerPtr = ownerPtr;
}

enf::GameObject* enf::Component::GetOwner() const
{
	return m_OwnerPtr;
}

void enf::Component::MarkForMurder()
{
	m_Delete = true;
}

bool enf::Component::IsMarked() const
{
	return m_Delete;
}
