#pragma once

namespace enf
{
	class InputMap;
	class GameObject;

	class Command
	{
		friend InputMap;

	public:
		virtual ~Command() = default;

		Command(Command&& other) = delete;
		Command(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;

		virtual void Execute() = 0;

	protected:
		Command() = default;
	};
}
