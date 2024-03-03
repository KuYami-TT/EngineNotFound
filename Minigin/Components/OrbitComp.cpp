#include "OrbitComp.h"
#include "GameObject.h"
#include "glm/trigonometric.hpp"
#include "glm/vec3.hpp"
#include "Managers/GameTime.h"

enf::OrbitComp::OrbitComp(float speed, float radius) :
	m_Speed{speed}
{
	m_Radius = radius;
}

void enf::OrbitComp::Update()
{
	m_Angle += m_Speed * game_time::Delta();

	const glm::vec3 newPos{ m_Radius * glm::cos(m_Angle), m_Radius * glm::sin(m_Angle), 0.f };
	GetOwner()->SetLocalPos(newPos);
}

void enf::OrbitComp::SetAngle(float angle)
{
	m_Angle = glm::radians(angle);
}
