#pragma once
#include <string>

namespace enf
{
	class Widget final
	{
	public:
		Widget(std::string windowName);
		~Widget() = default;

		Widget(Widget&& other) = delete;
		Widget(const Widget& other) = delete;
		Widget& operator=(Widget&& other) = delete;
		Widget& operator=(const Widget& other) = delete;

		[[nodiscard]] const std::string& GetName() const { return m_Name; }

		void Render();

		//Mark for deletion
		void MarkForMurder();
		[[nodiscard]] bool IsMarked() const;

	protected:
		std::string m_Name{};

	private:
		bool m_Delete{};
	};
}
