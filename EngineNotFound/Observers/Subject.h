#pragma once
#include <memory>
#include <vector>

#include "Observers/Observer.h"

namespace enf
{
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(const Observer* observer);

	protected:
		void NotifyObservers(GameObject* gameObject, Event event);
		std::vector<Observer*> m_Observers{};
	};
}
