#include "SpriteRenderComp.h"
#include "TransformComp.h"
#include "../Renderer.h"
#include "Managers/ResourceManager.h"

enf::SpriteRenderComp::SpriteRenderComp(const std::string& filename) :
	RenderComp()
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(filename);
}

void enf::SpriteRenderComp::Render()
{
	const glm::vec3& pos = m_TransformPtr->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
}
