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

	for (auto&& widget : m_WidgetsPtr)
	{
		widget->Render();
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

enf::Widget* enf::GUI::AddWidget(const std::string& windowName)
{
	if(HasWindow(windowName))
		return nullptr;

	const auto& newWidgetPtr = m_WidgetsPtr.emplace_back(std::make_unique<Widget>(windowName));
	
	return newWidgetPtr.get();
}

bool enf::GUI::HasWindow(const std::string& windowName)
{
	return std::ranges::any_of(m_WidgetsPtr,
		[&](const std::unique_ptr<Widget>& widget)->bool
		{
			return widget->GetName() == windowName;
		});
}

void enf::GUI::CheckToMurder()
{
	std::erase_if(m_WidgetsPtr, 
		[](const std::unique_ptr<Widget>& widget)
		{
			return widget->IsMarked();
		});
}
