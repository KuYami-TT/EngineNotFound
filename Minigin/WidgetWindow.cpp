#include "WidgetWindow.h"

#include <algorithm>

#include "imgui-docking/imgui.h"

enf::WidgetWindow::WidgetWindow(std::string windowName)
	: m_Name{ std::move(windowName) }
{
}

const std::string& enf::WidgetWindow::GetName() const
{
	return m_Name;
}

bool enf::WidgetWindow::HasWidget(const std::string& widgetName)
{
	return std::ranges::any_of(m_WidgetsPtr,
		[&](const std::unique_ptr<Widget>& widget)->bool
		{
			return widget->GetName() == widgetName;
		});
}

void enf::WidgetWindow::Render() const
{
	ImGui::Begin(m_Name.c_str());
	for (auto&& widget : m_WidgetsPtr)
	{
		widget->Render();
	}
	ImGui::End();
}

void enf::WidgetWindow::MarkForMurder()
{
	m_Delete = true;
}

bool enf::WidgetWindow::IsMarked() const
{
	return m_Delete;
}

void enf::WidgetWindow::CheckToMurder()
{
	std::erase_if(m_WidgetsPtr,
		[](const std::unique_ptr<Widget>& widget)->bool
		{
			return widget->IsMarked();
		});
}
