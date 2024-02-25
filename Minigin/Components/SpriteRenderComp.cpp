#include "SpriteRenderComp.h"
#include "TransformComp.h"
#include "../Renderer.h"
#include "Managers/ResourceManager.h"

enf::SpriteRenderComp::SpriteRenderComp(const std::string& filename) :
	RenderComp()
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void enf::SpriteRenderComp::Render()
{
	const glm::vec3& pos = m_pTransform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
