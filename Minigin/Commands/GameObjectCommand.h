#pragma once
#include "Command.h"

namespace enf
{
	class InputManager;
	class GameObject;

	class GameObjectCommand : public Command
	{
		friend InputManager;

	public:
		[[nodiscard]] inline GameObject* GetPossessed() const { return m_PossessedPtr; }

	protected:
		GameObjectCommand() = default;

	private:
		inline void SetPossessed(GameObject* gameObject) { m_PossessedPtr = gameObject; }
		GameObject* m_PossessedPtr{};
	};
}
