#include "MoveCommand.h"

#include "GameObject.h"
#include "Components/MoveComp.h"

void enf::MoveUpCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->MoveUp();
}

void enf::MoveLeftCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->MoveLeft();
}

void enf::MoveRightCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->MoveRight();
}

void enf::MoveDownCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->MoveDown();
}
