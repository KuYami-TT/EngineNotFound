#include "Widget.h"

#include "imgui-docking/imgui.h"

enf::Widget::Widget(std::string windowName)
	: m_Name{ std::move(windowName) }
{
}

void enf::Widget::Render()
{
	ImGui::Begin(m_Name.c_str());
	ImGui::End();
}

void enf::Widget::MarkForMurder()
{
	m_Delete = true;
}

bool enf::Widget::IsMarked() const
{
	return m_Delete;
}
