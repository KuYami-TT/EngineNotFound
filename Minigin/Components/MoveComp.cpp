#include "MoveComp.h"

#include "GameObject.h"
#include "Managers/GameTime.h"

enf::MoveComp::MoveComp(float speed) :
	m_Speed{ speed }
{
}

void enf::MoveComp::MoveUp()
{
	GetOwner()->SetLocalPos(GetOwner()->GetLocalPos() + glm::vec3(0, -m_Speed, 0) * game_time::Delta());
}

void enf::MoveComp::MoveLeft()
{
	GetOwner()->SetLocalPos(GetOwner()->GetLocalPos() + glm::vec3(-m_Speed, 0, 0) * game_time::Delta());
}

void enf::MoveComp::MoveRight()
{
	GetOwner()->SetLocalPos(GetOwner()->GetLocalPos() + glm::vec3(m_Speed, 0, 0) * game_time::Delta());
}

void enf::MoveComp::MoveDown()
{
	GetOwner()->SetLocalPos(GetOwner()->GetLocalPos() + glm::vec3(0, m_Speed, 0) * game_time::Delta());
}
