#pragma once
#include "GameEvent.h"

namespace enf
{
	class GameObject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		Observer(Observer&& other) = delete;
		Observer(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;

		virtual void Notify(GameObject* gameObject, Event event) = 0;
	};
}