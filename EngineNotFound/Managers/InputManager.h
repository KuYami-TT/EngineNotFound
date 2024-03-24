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
		InputManager() = default;
		~InputManager() override = default;

		bool ProcessInput();
		void AddController(GameObject* possessed, InputMap* inputMap);
		InputMap* AddInputMap();

	private:
		//TODO: make it so, I don't need to forward declare the class
		//TODO: fix the fact I can only use one pimpl here
		//TODO: You're missing an abstraction -> a gamepad??


		const int m_MaxControllers{ 4 };
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
		std::vector<std::unique_ptr<InputMap>> m_InputMaps{};

		SDL_KeyCode EngineButtonToSDL_KeyCode(Action::KeyboardLayout button);
		SDL_Scancode EngineButtonToSDL_Scanecode(Action::KeyboardLayout button);
	};
}