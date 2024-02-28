#include "GameObject.h"
#include "Managers/ResourceManager.h"
#include "Components/TransformComp.h"

enf::GameObject::GameObject(const glm::vec3& pos)
{
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

void enf::GameObject::CheckToMurder()
{
	std::erase_if(m_ComponentsPtr, 
		[](const std::unique_ptr<Component>& comp)->bool
		{
			return comp->IsMarked();
		});
}