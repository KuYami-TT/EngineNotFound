#include "ActionCommand.h"

#include "GameObject.h"
#include "Components/LivesComp.h"
#include "Components/ScoreComp.h"

void enf::TakeDamageCommand::Execute()
{
	GetPossessed()->GetComponent<LivesComp>()->TakeDamage();
}

void enf::GetPointsCommand::Execute()
{
	GetPossessed()->GetComponent<ScoreComp>()->ChangeScore(m_Points);
}
