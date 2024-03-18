#pragma once

#include <memory>
#include <vector>

#include "Action.h"
#include "Controller.h"
#include "Singleton.h"

namespace enf
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager() override;

		bool ProcessInput();
		void AddController(GameObject* possessed, InputMap* inputMap);
		InputMap* AddInputMap();

	private:
		class XInputImp;
		std::unique_ptr<XInputImp> m_ControllerImplPtr;

		const int m_MaxControllers{ 4 };
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
		std::vector<std::unique_ptr<InputMap>> m_InputMaps{};
		
		void HandleControllerEvent();
		SDL_KeyCode EngineButtonToSDL_KeyCode(Action::KeyboardLayout button);
		SDL_Scancode EngineButtonToSDL_scanecode(Action::KeyboardLayout button);
	};
}