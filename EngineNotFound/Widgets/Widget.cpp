#include "Widget.h"

enf::WidgetWindow* enf::Widget::GetOwner() const
{
	return m_OwnerPtr;
}

const std::string& enf::Widget::GetName() const
{
	return m_Name;
}

void enf::Widget::MarkForMurder()
{
	m_Delete = true;
}

bool enf::Widget::IsMarked() const
{
	return m_Delete;
}

enf::Widget::Widget(std::string widgetName)
	: m_Name{std::move(widgetName)}
{
}

void enf::Widget::SetOwner(WidgetWindow* ownerPtr)
{
	m_OwnerPtr = ownerPtr;
}
