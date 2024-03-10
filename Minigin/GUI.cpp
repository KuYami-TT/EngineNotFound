#include "GUI.h"

#include <algorithm>

#include "imgui-docking/imgui.h"
#include "imgui-docking/backends/imgui_impl_sdl2.h"
#include "imgui-docking/backends/imgui_impl_sdlrenderer2.h"

void enf::GUI::Init(SDL_Window* windowPtr, SDL_Renderer* rendererPtr)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(windowPtr, rendererPtr);
	ImGui_ImplSDLRenderer2_Init(rendererPtr);
}

void enf::GUI::Render()
{
	BeginFrame();

	for (auto&& widgetWindow : m_WidgetsWindowPtr)
	{
		widgetWindow->Render();
	}

	EndFrame();
}

void enf::GUI::BeginFrame() const
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void enf::GUI::EndFrame() const
{
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void enf::GUI::Destroy()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

enf::WidgetWindow* enf::GUI::AddWidgetWindow(const std::string& windowName)
{
	if(HasWindow(windowName))
		return nullptr;

	const auto& newWidgetPtr = m_WidgetsWindowPtr.emplace_back(std::make_unique<WidgetWindow>(windowName));
	
	return newWidgetPtr.get();
}

enf::WidgetWindow* enf::GUI::GetWidgetWindow(const std::string& windowName)
{
	const auto& foundWindow = 
		std::ranges::find_if(m_WidgetsWindowPtr,
			[&](const std::unique_ptr<WidgetWindow>& widgetWindow)->bool
			{
				return widgetWindow->GetName() == windowName;
			});

	if (foundWindow == m_WidgetsWindowPtr.end())
		return nullptr;

	return foundWindow->get();
}

bool enf::GUI::HasWindow(const std::string& windowName)
{
	return std::ranges::any_of(m_WidgetsWindowPtr,
		[&](const std::unique_ptr<WidgetWindow>& widgetWindow)->bool
		{
			return widgetWindow->GetName() == windowName;
		});
}

void enf::GUI::CheckToMurder()
{
	for (auto&& widget : m_WidgetsWindowPtr)
	{
		widget->CheckToMurder();
	}

	std::erase_if(m_WidgetsWindowPtr, 
		[](const std::unique_ptr<WidgetWindow>& widgetWindow)->bool
		{
			return widgetWindow->IsMarked();
		});
}
