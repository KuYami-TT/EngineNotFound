#include <stdexcept>
#include <utility>

#include "TextRenderComp.h"
#include "Font.h"
#include "Renderer.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "Texture2D.h"
#include "TransformComp.h"
#include "glm/vec3.hpp"

enf::TextRenderComp::TextRenderComp(std::shared_ptr<Font> pFont, std::string text) :
	RenderComp(),
	m_Text{std::move(text)},
	m_Font{std::move(pFont)},
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

void enf::TextRenderComp::Render()
{
	if(!m_TextTexture)
		return;

	const glm::vec3& pos = m_pTransform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
}

void enf::TextRenderComp::SetText(const std::string& text)
{
	if (text.empty())
	{
		m_Dirty = false;
		return;
	}

	constexpr SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextTexture = std::make_shared<Texture2D>(texture);
	m_Dirty = false;
}