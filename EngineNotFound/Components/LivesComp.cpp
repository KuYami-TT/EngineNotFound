#include "LivesComp.h"

enf::LivesComp::LivesComp(int lives) :
	m_Lives{ lives }
{
}

void enf::LivesComp::TakeDamage()
{
	--m_Lives;
	NotifyObservers(GetOwner(), Event::LivesChange);
}
