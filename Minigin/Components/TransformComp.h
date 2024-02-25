#pragma once
#include "../Component.h"
#include "glm/vec3.hpp"

namespace enf
{
	class TransformComp final : public Component
	{
	public:
		[[nodiscard]] const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3& pos);
	private:
		glm::vec3 m_position{};
	};
}
