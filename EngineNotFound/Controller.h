#pragma once

namespace enf
{
	class XInputImp;
	class InputMap;
	class GameObject;

	class Controller final
	{
	public:
		Controller(GameObject* possessed, InputMap* inputMap, int controllerIndex);
		~Controller();

		Controller(Controller&& other) = delete;
		Controller(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;

		void HandleControllerInput();

		GameObject* GetPossessed() const;
		InputMap* GetInputMap() const;

	private:
		XInputImp* m_ControllerImplPtr;
		GameObject* m_Possessed;
		InputMap* m_InputMap;
		int m_ControllerIndex{};
	};
}
