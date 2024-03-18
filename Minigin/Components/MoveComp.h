#pragma once
#include "Component.h"

namespace enf
{
	class MoveComp : public Component
	{
	public:
		MoveComp(float speed);
		~MoveComp() override = default;

		MoveComp(MoveComp&& other) = delete;
		MoveComp(const MoveComp& other) = delete;
		MoveComp& operator=(MoveComp&& other) = delete;
		MoveComp& operator=(const MoveComp& other) = delete;

		void MoveUp();
		void MoveLeft();
		void MoveRight();
		void MoveDown();

	private:
		float m_Speed;
	};
}
