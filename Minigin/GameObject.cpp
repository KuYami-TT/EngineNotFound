#include <string>
#include "GameObject.h"
#include "Managers/ResourceManager.h"
#include "Renderer.h"

enf::GameObject::~GameObject() = default;

void enf::GameObject::Awake(){}

void enf::GameObject::FixedUpdate(){}

void enf::GameObject::Update(){}

void enf::GameObject::LateUpdate(){}

void enf::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void enf::GameObject::CheckMarked()
{
	std::erase_if(m_Components, [](const std::unique_ptr<Component>& comp)
		{
			return comp->IsMarked();
		});
}

void enf::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void enf::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
