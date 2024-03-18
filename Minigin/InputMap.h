#pragma once
#include <map>
#include <memory>

#include "Action.h"
#include "Commands/Command.h"

namespace enf
{
	template<typename CommandType>
	concept ICommand = requires(CommandType c)
	{
		{ std::derived_from<CommandType, Command> };
	};

	class InputMap final
	{
	public:
		InputMap() = default;
		~InputMap() = default;

		InputMap(InputMap&& other) = delete;
		InputMap(const InputMap& other) = delete;
		InputMap& operator=(InputMap&& other) = delete;
		InputMap& operator=(const InputMap& other) = delete;

		template<ICommand CommandType, typename... TArgs>
		void BindAction(Action::InputState inputState, Action::ControllerLayout input, const TArgs&... args)
		{
			m_ControllerActionMap.emplace(std::make_unique<Action>(inputState, input), std::make_unique<CommandType>(args...));
		}

		template<ICommand CommandType, typename... TArgs>
		void BindAction(Action::InputState inputState, Action::KeyboardLayout input, const TArgs&... args)
		{
			m_KeyboardActionMap.emplace(std::make_unique<Action>(inputState, input), std::make_unique<CommandType>(args...));
		}

		const std::map<std::unique_ptr<Action>, std::unique_ptr<Command>>& GetControllerMap();
		const std::map<std::unique_ptr<Action>, std::unique_ptr<Command>>& GetKeyboardMap();

	private:
		std::map<std::unique_ptr<Action>, std::unique_ptr<Command>> m_ControllerActionMap{};
		std::map<std::unique_ptr<Action>, std::unique_ptr<Command>> m_KeyboardActionMap{};
	};

	inline const std::map<std::unique_ptr<Action>, std::unique_ptr<Command>>& InputMap::GetControllerMap()
	{
		return m_ControllerActionMap;
	}

	inline const std::map<std::unique_ptr<Action>, std::unique_ptr<Command>>& InputMap::GetKeyboardMap()
	{
		return m_KeyboardActionMap;
	}
}
