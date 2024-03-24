#include "Subject.h"

void enf::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(std::unique_ptr<Observer>(observer));
}

void enf::Subject::RemoveObserver(const Observer* observer)
{
	const auto it = 
		std::ranges::find_if(m_Observers, [&](const std::unique_ptr<Observer>& ptr)->bool 
			{
				return ptr.get() == observer;
			});

	if (it != m_Observers.end()) 
		return;

	m_Observers.erase(it);
}

void enf::Subject::NotifyObservers(GameObject* gameObject, Event event)
{
	for (auto&& observer : m_Observers)
	{
		observer->Notify(gameObject, event);
	}
}