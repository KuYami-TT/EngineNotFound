#include "SpriteRenderComp.h"
#include "Managers/ResourceManager.h"

enf::SpriteRenderComp::SpriteRenderComp(const std::string& filename) :
	RenderComp()
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(filename);
}
