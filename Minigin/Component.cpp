#include "Component.h"

#include "GameObject.h"

void enf::Component::SetParent(GameObject* parentPtr)
{
	m_ParentPtr = parentPtr;
}

enf::GameObject* enf::Component::GetParent() const
{
	return m_ParentPtr;
}

void enf::Component::MarkForMurder()
{
	m_Delete = true;
}

bool enf::Component::IsMarked() const
{
	return m_Delete;
}
