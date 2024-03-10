#pragma once
#include <memory>
#include <vector>

#include "Singleton.h"
#include "Widget.h"

struct SDL_Window;
struct SDL_Renderer;

namespace enf
{
	/**
	* Simple RAII wrapper for the ImGUI renderer
	* Inspired by mat with no hat
	*/
	template<typename WidgetType>
	concept IWidget = requires(WidgetType c)
	{
		{ std::derived_from<WidgetType, Widget> };
	};

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
		void Render();
		void Destroy();

		Widget* AddWidget(const std::string& windowName);

		//Delete components that are marked for deletion 
		void CheckToMurder();

	private:
		std::vector<std::unique_ptr<Widget>> m_WidgetsPtr{};

		bool HasWindow(const std::string& windowName);

		void BeginFrame() const;
		void EndFrame() const;
	};
}
