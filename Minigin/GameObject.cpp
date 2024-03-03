#include "GameObject.h"
#include "Managers/ResourceManager.h"

enf::GameObject::GameObject(const std::string& name, const glm::vec3& pos)
{
	m_Name = name;
	SetLocalPos(pos);
}

void enf::GameObject::Awake()
{
	for (auto&& comp : m_ComponentsPtr)
	{
		comp->Awake();
	}
}

void enf::GameObject::FixedUpdate()
{
	for (auto&& comp : m_ComponentsPtr)
	{
		if (comp->IsMarked())
			continue;

		comp->FixedUpdate();
	}
}

void enf::GameObject::Update()
{
	for (auto&& comp : m_ComponentsPtr)
	{
		if (comp->IsMarked())
			continue;

		comp->Update();
	}
}

void enf::GameObject::LateUpdate()
{
	for (auto&& comp : m_ComponentsPtr)
	{
		if (comp->IsMarked())
			continue;

		comp->LateUpdate();
	}
}

void enf::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	if (parent == this) {
		assert(false && "Error: GameObject cannot be its own parent");
		return;
	}

	if (IsChild(parent)) {
		assert(false && "Error: Child cannot be set as parent");
		return;
	}

	if(m_ParentPtr == parent)
		return;

	if (parent == nullptr)
		SetLocalPos(GetWorldPos());
	else
	{
		if (keepWorldPos)
			SetLocalPos(GetWorldPos() - parent->GetWorldPos());
		SetPosDirty();
	}

	if (m_ParentPtr)
		m_ParentPtr->RemoveChild(this);

	m_ParentPtr = parent;

	if (m_ParentPtr)
		m_ParentPtr->AddChild(this);
}

const glm::vec3& enf::GameObject::GetWorldPos()
{
	if (m_PosDirty)
		UpdateWorldPos();
	return m_WorldPos;
}

void enf::GameObject::SetLocalPos(const glm::vec3& pos)
{
	m_LocalPos = pos;
	SetPosDirty();
}

void enf::GameObject::MarkForMurder()
{
	m_Delete = true;

	for (const auto child : m_ChildrenPtrVec)
	{
		child->MarkForMurder();
	}
}

bool enf::GameObject::IsMarked() const
{
	return m_Delete;
}

void enf::GameObject::CheckToMurder()
{
	std::erase_if(m_ComponentsPtr, 
		[](const std::unique_ptr<Component>& comp)->bool
		{
			return comp->IsMarked();
		});
}

void enf::GameObject::AddChild(GameObject* child)
{
	m_ChildrenPtrVec.push_back(child);
}

void enf::GameObject::RemoveChild(GameObject* child)
{
	std::erase(m_ChildrenPtrVec, child);
}

bool enf::GameObject::IsChild(GameObject* child)
{
	const auto foundChild = std::ranges::find(m_ChildrenPtrVec, child);
	return foundChild != m_ChildrenPtrVec.end();
}

void enf::GameObject::UpdateWorldPos()
{
	if(!m_PosDirty)
		return;

	if (m_ParentPtr == nullptr)
		m_WorldPos = m_LocalPos;
	else
		m_WorldPos = m_ParentPtr->GetWorldPos() + m_LocalPos;

	m_PosDirty = false;
}

void enf::GameObject::SetPosDirty()
{
	m_PosDirty = true;
}
