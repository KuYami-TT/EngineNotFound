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
		using Mappings = std::map<std::unique_ptr<Action>, std::unique_ptr<Command>>;

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

		const Mappings& GetControllerMap();
		const Mappings& GetKeyboardMap();
		const Mappings& GetControllerMap() const;
		const Mappings& GetKeyboardMap() const;

	private:
		Mappings m_ControllerActionMap{};
		Mappings m_KeyboardActionMap{};
	};

	inline const InputMap::Mappings& InputMap::GetControllerMap()
	{
		return m_ControllerActionMap;
	}

	inline const InputMap::Mappings& InputMap::GetKeyboardMap()
	{
		return m_KeyboardActionMap;
	}
}
