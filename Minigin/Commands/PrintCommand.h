#pragma once
#include "Command.h"

namespace enf
{
	class PrintCommand final : public Command
	{
	public:
		PrintCommand() = default;
		~PrintCommand() override = default;

		PrintCommand(PrintCommand&& other) = delete;
		PrintCommand(const PrintCommand& other) = delete;
		PrintCommand& operator=(PrintCommand&& other) = delete;
		PrintCommand& operator=(const PrintCommand& other) = delete;

		void Execute() override;
	};
}