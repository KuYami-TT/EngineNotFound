#include <stdexcept>
#include <utility>

#include "TextRenderComp.h"
#include "Renderer.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "Texture2D.h"

enf::TextRenderComp::TextRenderComp(Font* fontPtr, std::string text) :
	RenderComp(),
	m_Text{std::move(text)},
	m_FontPtr{fontPtr},
	m_Dirty{true}
{
}

void enf::TextRenderComp::Update()
{
	if(m_Dirty)
	{
		SetText(m_Text);
	}
}

void enf::TextRenderComp::SetText(const std::string& text)
{
	if (text.empty())
	{
		m_Dirty = false;
		return;
	}

	constexpr SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surfPtr = TTF_RenderText_Blended(m_FontPtr->GetFont(), text.c_str(), color);
	if (surfPtr == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::Get().GetSDLRenderer(), surfPtr);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surfPtr);
	m_TextTexturePtr = std::make_unique<Texture2D>(texture);
	m_TexturePtr = m_TextTexturePtr.get();
	m_Dirty = false;
}