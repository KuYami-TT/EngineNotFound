#pragma once
#include <deque>
#include <memory>

#include "../Component.h"

namespace enf
{
	class TextRenderComp;
	class Font;

	class FPSComp final : public Component
	{
	public:
		FPSComp(std::shared_ptr<Font> pFont);
		~FPSComp() override = default;

		FPSComp(FPSComp&& other) = delete;
		FPSComp(const FPSComp& other) = delete;
		FPSComp& operator=(FPSComp&& other) = delete;
		FPSComp& operator=(const FPSComp& other) = delete;

		void Awake() override;
		void Update() override;

	private:
		bool m_NeedsUpdate;
		int m_Precision{ 1 };
		float m_UpdateDelay{ .5f };
		double m_Timer{};
		TextRenderComp* m_pTextRenderComp{};
		std::shared_ptr<Font> m_pFont;

		std::deque<double> m_TotalFPS{};

		double GetAverageFps();
	};
}
