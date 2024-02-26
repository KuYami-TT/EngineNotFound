#include "SpriteRender.h"

enf::SpriteRenderComp::SpriteRenderComp(std::shared_ptr<Texture2D> pTexture) :
	RenderComp(),
	m_pTexture{std::move(pTexture)}
{
}

void enf::SpriteRenderComp::Render()
{
	
}
