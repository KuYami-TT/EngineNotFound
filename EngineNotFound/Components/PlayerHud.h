#pragma once
#include "Component.h"
#include "Observers/Observer.h"
#include "Observers/Subject.h"

namespace enf
{
	class Font;
	class TextRenderComp;
	class GameObject;
	class PlayerHud final : public Component, public Observer, public Subject
	{
	public:
		PlayerHud(Font* fontPtr, int startLives);
		~PlayerHud() override = default;

		PlayerHud(PlayerHud&& other) = delete;
		PlayerHud(const PlayerHud& other) = delete;
		PlayerHud& operator=(PlayerHud&& other) = delete;
		PlayerHud& operator=(const PlayerHud& other) = delete;

		void Awake() override;

		void Notify(GameObject* gameObject, Event event) override;

	private:
		TextRenderComp* m_LivesText{};
		TextRenderComp* m_ScoreText{};
		Font* m_FontPtr{};
		int m_StartLives{};
		int m_Score{};

		void UpdateLives(int lives);
		void UpdateScore(int score);
	};
}
