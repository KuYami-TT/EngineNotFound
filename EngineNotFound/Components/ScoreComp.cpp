#include "ScoreComp.h"

void enf::ScoreComp::ChangeScore(int points)
{
	m_ReceivedPoints = points;
	NotifyObservers(GetOwner(), Event::OnPickUp);
}
