#include <SDL.h>
#include "Texture2D.h"

enf::Texture2D::Texture2D(SDL_Texture* texturePtr)
{
	m_TexturePtr = texturePtr;
}

enf::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_TexturePtr);
}

glm::ivec2 enf::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* enf::Texture2D::GetSDLTexture() const
{
	return m_TexturePtr;
}