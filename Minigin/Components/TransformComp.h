#pragma once
#include "../Component.h"
#include "glm/vec3.hpp"

namespace enf
{
	class TransformComp final : public Component
	{
	public:
		TransformComp() = default;
		~TransformComp() override = default;

		TransformComp(TransformComp&& other) = delete;
		TransformComp(const TransformComp& other) = delete;
		TransformComp& operator=(TransformComp&& other) = delete;
		TransformComp& operator=(const TransformComp& other) = delete;

		[[nodiscard]] const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3& pos);
	private:
		glm::vec3 m_position{};
	};
}
