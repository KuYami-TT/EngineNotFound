#include "MoveCommand.h"

#include "GameObject.h"
#include "Components/MoveComp.h"

//TODO: try to use the return value of input to make an input vec (so we only need one move command)
void enf::MoveUpCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->Move(glm::vec2(0, -1));
}

void enf::MoveLeftCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->Move(glm::vec2(-1, 0));
}

void enf::MoveRightCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->Move(glm::vec2(1, 0));
}

void enf::MoveDownCommand::Execute()
{
	GetPossessed()->GetComponent<MoveComp>()->Move(glm::vec2(0, 1));
}
