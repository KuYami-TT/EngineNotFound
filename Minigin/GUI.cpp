#include "GUI.h"

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
