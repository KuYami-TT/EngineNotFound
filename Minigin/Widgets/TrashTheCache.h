#pragma once
#include "Widget.h"

namespace enf
{
	class TrashTheCache final : public Widget
	{
	public:
		TrashTheCache(const std::string& widgetName);
		~TrashTheCache() override = default;

		TrashTheCache(TrashTheCache&& other) = delete;
		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;

		void Render() override;
	};
}
