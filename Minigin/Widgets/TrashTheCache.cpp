#include "TrashTheCache.h"

#include "imgui-docking/imgui.h"

enf::TrashTheCache::TrashTheCache(const std::string& widgetName)
	: Widget{ widgetName }
{
}

void enf::TrashTheCache::Render()
{
	ImGui::Text("Hello world!");
}
