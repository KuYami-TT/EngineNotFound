#pragma once
#include "Component.h"
#include "Observers/Observer.h"

namespace enf
{
	class Font;
	class TextRenderComp;
	class GameObject;
	class PlayerHud final : public Component, public Observer
	{
	public:
		PlayerHud(Font* fontPtr);
		~PlayerHud() override = default;

		PlayerHud(PlayerHud&& other) = delete;
		PlayerHud(const PlayerHud& other) = delete;
		PlayerHud& operator=(PlayerHud&& other) = delete;
		PlayerHud& operator=(const PlayerHud& other) = delete;

		auto Awake() -> void override;

		void Notify(GameObject* gameObject, Event event) override;

	private:
		TextRenderComp* m_LivesText{};
		TextRenderComp* m_ScoreText{};
		Font* m_FontPtr{};

		void UpdateLives(int lives);
		void UpdateScore(int score);
	};
}
