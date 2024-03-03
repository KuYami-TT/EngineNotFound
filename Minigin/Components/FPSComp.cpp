#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>

#include "FPSComp.h"
#include "../Managers/GameTime.h"
#include "GameObject.h"
#include "TextRenderComp.h"

enf::FPSComp::FPSComp(std::shared_ptr<Font> fontPtr) :
	Component(),
	m_NeedsUpdate{true},
	m_FontPtr{std::move(fontPtr)}
{
}

void enf::FPSComp::Awake()
{
	m_TextRenderCompPtr = GetOwner()->AddComponent<TextRenderComp>(m_FontPtr);
}

void enf::FPSComp::Update()
{
	if(m_TextRenderCompPtr == nullptr)
		return;

	if(m_NeedsUpdate)
	{
		m_Timer -= static_cast<double>(m_UpdateDelay);

		std::stringstream textBuffer;
		textBuffer << std::fixed << std::setprecision(m_Precision) << GetAverageFps();
		textBuffer << " FPS";

		m_TextRenderCompPtr->SetText(textBuffer.str());
		m_TotalFPS.clear();
			
		m_NeedsUpdate = false;
	}

	m_TotalFPS.push_back(game_time::FPS());
	m_Timer += game_time::Delta();
	m_NeedsUpdate = m_Timer > static_cast<double>(m_UpdateDelay);
}

void enf::FPSComp::SetPrecision(int newPrecision)
{
	m_Precision = newPrecision;
}

double enf::FPSComp::GetAverageFps()
{
	if (m_TotalFPS.size() < 2)
		return game_time::FPS();

	std::ranges::sort(m_TotalFPS);

	m_TotalFPS.pop_front();
	m_TotalFPS.pop_back();

	if (m_TotalFPS.empty())
		return game_time::FPS();

	return std::accumulate(m_TotalFPS.begin(), m_TotalFPS.end(), 0.) / static_cast<double>(m_TotalFPS.size());
}
