#pragma once
#include "Component.h"

namespace enf
{
	class OrbitComp final : public Component
	{
	public:
		OrbitComp(float speed, float radius);
		~OrbitComp() override = default;

		OrbitComp(OrbitComp&& other) = delete;
		OrbitComp(const OrbitComp& other) = delete;
		OrbitComp& operator=(OrbitComp&& other) = delete;
		OrbitComp& operator=(const OrbitComp& other) = delete;

		void Update() override;
		void SetAngle(float angle);

	private:
		float m_Speed;
		float m_Radius;
		float m_Angle{};
	};
}