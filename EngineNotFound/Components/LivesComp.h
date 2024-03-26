#pragma once
#include "Component.h"
#include "Observers/Subject.h"

namespace enf
{
	class LivesComp final : public Component, public Subject
	{
	public:
		LivesComp(int lives);
		~LivesComp() override = default;

		LivesComp(LivesComp&& other) = delete;
		LivesComp(const LivesComp& other) = delete;
		LivesComp& operator=(LivesComp&& other) = delete;
		LivesComp& operator=(const LivesComp& other) = delete;

		inline int GetLives() const { return m_Lives; }
		void TakeDamage();

	private:
		int m_Lives{};
	};
}