#pragma once

#include <memory>
#include <vector>

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
		std::unique_ptr<XInputImp> m_ImplPtr;
		std::vector<std::unique_ptr<InputMap>> m_InputMaps{};
	};
}