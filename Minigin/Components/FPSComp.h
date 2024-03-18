#pragma once
#include <deque>
#include <memory>

#include "Component.h"
#include "Font.h"

namespace enf
{
	class TextRenderComp;

	class FPSComp final : public Component
	{
	public:
		FPSComp(Font* fontPtr);
		~FPSComp() override = default;

		FPSComp(FPSComp&& other) = delete;
		FPSComp(const FPSComp& other) = delete;
		FPSComp& operator=(FPSComp&& other) = delete;
		FPSComp& operator=(const FPSComp& other) = delete;

		void Awake() override;
		void Update() override;

		void SetPrecision(int newPrecision);

	private:
		bool m_NeedsUpdate;
		int m_Precision{ 1 };
		float m_UpdateDelay{ .5f };
		float m_Timer{};
		TextRenderComp* m_TextRenderCompPtr{};
		Font* m_FontPtr;

		std::deque<float> m_TotalFPS{};

		float GetAverageFps();
	};
}
