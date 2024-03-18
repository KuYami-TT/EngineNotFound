#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Widget.h"

namespace enf
{
	template<typename WidgetType>
	concept IWidget = requires(WidgetType c)
	{
		{ std::derived_from<WidgetType, Widget> };
	};

	class WidgetWindow final
	{
	public:
		WidgetWindow(std::string windowName);
		~WidgetWindow() = default;

		WidgetWindow(WidgetWindow&& other) = delete;
		WidgetWindow(const WidgetWindow& other) = delete;
		WidgetWindow& operator=(WidgetWindow&& other) = delete;
		WidgetWindow& operator=(const WidgetWindow& other) = delete;

		[[nodiscard]] const std::string& GetName() const;

		template<IWidget WidgetType, typename... TArgs>
		WidgetType* AddWidget(const std::string& widgetName, const TArgs&... args)
		{
			if (HasWidget(widgetName))
				return nullptr;

			auto& newWidgetPtr = m_WidgetsPtr.emplace_back(std::make_unique<WidgetType>(widgetName, args...));
			newWidgetPtr->SetOwner(this);

			return reinterpret_cast<WidgetType*>(newWidgetPtr.get());
		}

		template<IWidget WidgetType>
		WidgetType* GetWidget(const std::string& widgetName)
		{
			const auto foundWidget =
				std::ranges::find_if(m_WidgetsPtr,
				[&](const std::unique_ptr<Widget>& widget)->bool
				{
					return widget->GetName() == widgetName;
				});

			if (foundWidget == m_WidgetsPtr.end())
				return nullptr;

			return dynamic_cast<WidgetType*>(foundWidget->get());
		}

		void Render() const;

		//Mark for deletion
		void MarkForMurder();
		[[nodiscard]] bool IsMarked() const;

		//Delete Widgets that are marked for deletion 
		void CheckToMurder();

	protected:
		std::string m_Name{};

	private:
		bool m_Delete{};
		std::vector<std::unique_ptr<Widget>> m_WidgetsPtr{};

		bool HasWidget(const std::string& widgetName);
	};
}
