#include "PrintCommand.h"

#include "SDL_syswm.h"

void enf::PrintCommand::Execute()
{
	OutputDebugString("Executed print command!\n");
}
