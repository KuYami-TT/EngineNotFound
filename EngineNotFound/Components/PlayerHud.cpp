#include <fmt/format.h>

#include "PlayerHud.h"

#include "LivesComp.h"
#include "ScoreComp.h"
#include "TextRenderComp.h"

enf::PlayerHud::PlayerHud(Font* fontPtr, int startLives) :
	Observer(),
	m_FontPtr{ fontPtr },
	m_StartLives{ startLives }
{

}

void enf::PlayerHud::Awake()
{
	m_LivesText = GetOwner()->AddComponent<TextRenderComp>(m_FontPtr);

	m_ScoreText = GetOwner()->AddComponent<TextRenderComp>(m_FontPtr);
	m_ScoreText->SetOffset({ 0, 25 });

	UpdateLives(m_StartLives);
	UpdateScore(0);
}

void enf::PlayerHud::Notify([[maybe_unused]] GameObject* gameObject, Event event)
{
	switch (event) {
	case Event::LivesChange:
		UpdateLives(gameObject->GetComponent<LivesComp>()->GetLives());
		break;
	case Event::OnPickUp:
		UpdateScore(gameObject->GetComponent<ScoreComp>()->GetReceivedPoints());
		break;
	}
}

void enf::PlayerHud::UpdateLives(int lives)
{
	m_LivesText->SetText(fmt::format("# LIVES: {}", lives));
}

void enf::PlayerHud::UpdateScore(int score)
{
	m_Score += score;
	m_ScoreText->SetText(fmt::format("SCORE: {}", m_Score));
}