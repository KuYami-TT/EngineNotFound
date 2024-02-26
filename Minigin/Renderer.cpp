#include <stdexcept>
#include <cstring>
#include "Renderer.h"
#include "Managers/SceneManager.h"
#include "Texture2D.h"

int GetOpenGLDriverIndex()
{
	int openglIndex = -1;
	const int driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void enf::Renderer::Init(SDL_Window* window)
{
	m_WindowPtr = window;
	m_RendererPtr = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_RendererPtr == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void enf::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_RendererPtr);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_RendererPtr);
}

void enf::Renderer::Destroy()
{
	if (m_RendererPtr != nullptr)
	{
		SDL_DestroyRenderer(m_RendererPtr);
		m_RendererPtr = nullptr;
	}
}

void enf::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void enf::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* enf::Renderer::GetSDLRenderer() const { return m_RendererPtr; }
