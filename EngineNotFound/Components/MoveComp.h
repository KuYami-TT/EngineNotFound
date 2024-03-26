#pragma once
#include "Component.h"
#include "glm/vec2.hpp"

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

		void Move(glm::vec2 inputVec) const;
		void MoveUp();
		void MoveLeft();
		void MoveRight();
		void MoveDown();

	private:
		float m_Speed;
	};
}
