#include <fmt/format.h>

#include "PlayerHud.h"
#include "TextRenderComp.h"

enf::PlayerHud::PlayerHud(Font* fontPtr) :
	Observer(),
	m_FontPtr{ fontPtr }
{
	UpdateLives(3);
	UpdateScore(0);
}

void enf::PlayerHud::Awake()
{
	m_LivesText = GetOwner()->AddComponent<TextRenderComp>(m_FontPtr);
	m_ScoreText = GetOwner()->AddComponent<TextRenderComp>(m_FontPtr);
}

void enf::PlayerHud::Notify([[maybe_unused]] GameObject* gameObject, Event event)
{
	switch (event) {
	case Event::OnTakeDamage:
		UpdateLives(1);
		break;
	case Event::OnSmallPickUp:
		UpdateScore(10);
		break;
	case Event::OnBigPickUp:
		UpdateScore(100);
		break;
	}
}

void enf::PlayerHud::UpdateLives(int lives)
{
	m_LivesText->SetText(fmt::format("LIVES: {}", lives));
}

void enf::PlayerHud::UpdateScore(int score)
{
	m_ScoreText->SetText(fmt::format("SCORE: {}", score));
}