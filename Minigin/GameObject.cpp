#include "GameObject.h"
#include "Managers/ResourceManager.h"
#include "Components/TransformComp.h"

enf::GameObject::GameObject(const std::string& name, const glm::vec3& pos)
{
	m_Name = name;
	AddComponent<TransformComp>()->SetPosition(pos);
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

void enf::GameObject::Render() const
{
	for (auto&& comp : m_ComponentsPtr)
	{
		if (comp->IsMarked())
			continue;

		comp->Render();
	}
}

void enf::GameObject::SetParent(GameObject* parent)
{
	assert(parent != this && "Error: GameObject with parent itself");
	if(parent == this)
		return;

	assert(!IsChild(parent) && "Error: Child can't be the parent, first remove child");
	if (IsChild(parent))
		return;

	if(m_ParentPtr == parent)
		return;

	if(m_ParentPtr == nullptr)
	{
		m_ParentPtr = parent;
		m_ParentPtr->AddChild(this);
	}
	else
	{
		m_ParentPtr->RemoveChild(this);
		m_ParentPtr = parent;
		m_ParentPtr->AddChild(this);
	}
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