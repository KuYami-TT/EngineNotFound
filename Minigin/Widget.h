#pragma once
#include <string>

namespace enf
{
	class WidgetWindow;

	class Widget
	{
		friend WidgetWindow;

	public:
		virtual ~Widget() = default;

		Widget( Widget&& other) = delete;
		Widget(const  Widget& other) = delete;
		Widget& operator=( Widget&& other) = delete;
		Widget& operator=(const  Widget& other) = delete;

		[[nodiscard]] WidgetWindow* GetOwner() const;
		[[nodiscard]] const std::string& GetName() const;

		virtual inline void Render() {}

		//Mark for deletion
		void MarkForMurder();
		[[nodiscard]] bool IsMarked() const;

	protected:
		Widget(std::string widgetName);

	private:
		WidgetWindow* m_OwnerPtr{};
		std::string m_Name{};
		bool m_Delete{};

		void SetOwner(WidgetWindow* ownerPtr);
	};
}
