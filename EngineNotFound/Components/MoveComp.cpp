#include "MoveComp.h"

#include "GameObject.h"
#include "glm/vec2.hpp"
#include "Managers/GameTime.h"

enf::MoveComp::MoveComp(float speed) :
	m_Speed{ speed }
{
}

void enf::MoveComp::Move(glm::vec2 inputVec) const
{
	GetOwner()->SetLocalPos(GetOwner()->GetLocalPos() + glm::vec3(m_Speed * inputVec, 0) * game_time::Delta());
}
