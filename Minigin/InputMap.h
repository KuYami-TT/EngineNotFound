#pragma once
#include <map>
#include <memory>
#include <vector>

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
			m_ActionList.emplace(std::make_unique<Action>(inputState, input), std::make_unique<CommandType>(args...));
		}

		std::map<std::unique_ptr<Action>, std::unique_ptr<Command>>& GetMap() { return m_ActionList; }

	private:
		std::map<std::unique_ptr<Action>, std::unique_ptr<Command>> m_ActionList{};
	};
}
