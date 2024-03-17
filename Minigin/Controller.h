#pragma once

namespace enf
{
	class InputMap;
	class GameObject;

	class Controller final
	{
	public:
		Controller(GameObject* possessed, InputMap* inputMap);
		~Controller() = default;

		Controller(Controller&& other) = delete;
		Controller(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;

		GameObject* GetPossessed() const;
		InputMap* GetInputMap() const;

		// doesn't work?
		//InputMap* GetInputMap() const { return m_InputMap; }

	private:
		GameObject* m_Possessed;
		InputMap* m_InputMap;
	};
}
