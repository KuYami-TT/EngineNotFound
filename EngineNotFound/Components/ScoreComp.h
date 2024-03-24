#pragma once
#include "Component.h"
#include "Observers/Subject.h"

namespace enf
{
	class ScoreComp final : public Component, public Subject
	{
	public:
		ScoreComp() = default;
		~ScoreComp() override = default;

		ScoreComp(ScoreComp&& other) = delete;
		ScoreComp(const ScoreComp& other) = delete;
		ScoreComp& operator=(ScoreComp&& other) = delete;
		ScoreComp& operator=(const ScoreComp& other) = delete;

		[[nodiscard]] int GetReceivedPoints() const { return m_ReceivedPoints; }
		void ChangeScore(int points);

	private:
		int m_ReceivedPoints{};
	};
}
