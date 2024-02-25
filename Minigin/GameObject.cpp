#include <string>
#include "GameObject.h"
#include "Managers/ResourceManager.h"
#include "Renderer.h"
#include "Components/TransformComp.h"

enf::GameObject::GameObject(const glm::vec3& pos)
{
	AddComponent<TransformComp>()->SetPosition(pos);
}

void enf::GameObject::Awake()
{
	for (auto&& comp : m_Components)
	{
		comp->Awake();
	}
}

void enf::GameObject::FixedUpdate()
{
	for (auto&& comp : m_Components)
	{
		comp->FixedUpdate();
	}
}

void enf::GameObject::Update()
{
	for (auto&& comp : m_Components)
	{
		comp->Update();
	}
}

void enf::GameObject::LateUpdate()
{
	for (auto&& comp : m_Components)
	{
		comp->LateUpdate();
	}
}

void enf::GameObject::Render() const
{
	//const auto& pos = m_transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);

	for (auto&& comp : m_Components)
	{
		comp->Render();
	}
}

void enf::GameObject::CheckMarked()
{
	std::erase_if(m_Components, 
		[](const std::unique_ptr<Component>& comp)->bool
		{
			return comp->IsMarked();
		});
}

void enf::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
