#pragma once
#include <memory>

#include "../Component.h"

namespace enf
{
	class TextRenderComp;
	class Font;

	class FPSComp final : public Component
	{
	public:
		FPSComp(const std::shared_ptr<Font>& pFont);
		~FPSComp() override = default;

		FPSComp(FPSComp&& other) = delete;
		FPSComp(const FPSComp& other) = delete;
		FPSComp& operator=(FPSComp&& other) = delete;
		FPSComp& operator=(const FPSComp& other) = delete;

	private:
		TextRenderComp* m_pTextRenderComp{};
	};
}
