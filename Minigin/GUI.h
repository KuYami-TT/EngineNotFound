#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace enf
{
	/**
	* Simple RAII wrapper for the ImGUI renderer
	*/
	class GUI final : public Singleton<GUI>
	{
	public:
		GUI() = default;
		~GUI() override = default;

		GUI(GUI&& other) = delete;
		GUI(const GUI& other) = delete;
		GUI& operator=(GUI&& other) = delete;
		GUI& operator=(const GUI& other) = delete;

		void Init(SDL_Window* windowPtr, SDL_Renderer* rendererPtr);
		void BeginFrame() const;
		void EndFrame() const;
		void Destroy();
	};
}
