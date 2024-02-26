#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>

#include "FPSComp.h"
#include "../Managers/GameTime.h"
#include "GameObject.h"
#include "TextRenderComp.h"

enf::FPSComp::FPSComp([[maybe_unused]] std::shared_ptr<Font> fontPtr) :
	Component(),
	m_FontPtr{std::move(fontPtr)},
	m_NeedsUpdate{true}
{
}

void enf::FPSComp::Awake()
{
	m_TextRenderCompPtr = GetParent()->AddComponent<TextRenderComp>(m_FontPtr);
}

void enf::FPSComp::Update()
{
	if(m_TextRenderCompPtr == nullptr)
		return;

	if(m_NeedsUpdate)
	{
		m_Timer -= m_UpdateDelay;

		std::stringstream textBuffer;
		textBuffer << std::fixed << std::setprecision(m_Precision) << GetAverageFps();
		textBuffer << " FPS";

		m_TextRenderCompPtr->SetText(textBuffer.str());
		m_TotalFPS.clear();
			
		m_NeedsUpdate = false;
	}

	m_TotalFPS.push_back(game_time::FPS());
	m_Timer += game_time::Delta();
	m_NeedsUpdate = m_Timer > m_UpdateDelay;
}

double enf::FPSComp::GetAverageFps()
{
	if (m_TotalFPS.empty())
		return game_time::FPS();

	std::ranges::sort(m_TotalFPS);

	m_TotalFPS.pop_front();
	m_TotalFPS.pop_back();

	if (m_TotalFPS.empty())
		return game_time::FPS();

	return std::accumulate(m_TotalFPS.begin(), m_TotalFPS.end(), 0.) / static_cast<double>(m_TotalFPS.size());
}
