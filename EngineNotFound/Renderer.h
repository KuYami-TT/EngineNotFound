#pragma once
#include <list>
#include <SDL.h>
#include "Singleton.h"

namespace enf
{
	class RenderComp;
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		Renderer() = default;
		~Renderer() override = default;

		Renderer(Renderer&& other) = delete;
		Renderer(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;

		void Init(SDL_Window* window);
		void Update();
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

		void SetDirty();

		void AddToRenderList(RenderComp* renderCompPtr);
		bool RemoveOutRenderList(RenderComp* renderCompPtr);

	private:
		bool m_Dirty{};

		SDL_Renderer* m_RendererPtr{};
		SDL_Window* m_WindowPtr{};
		SDL_Color m_ClearColor{};

		std::list<RenderComp*> m_RenderListPtr{};

		bool HasPtrInRenderList(RenderComp* renderCompPtr);
	};
}

