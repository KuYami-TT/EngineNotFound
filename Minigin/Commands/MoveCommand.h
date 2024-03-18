#pragma once
#include "GameObjectCommand.h"

namespace enf
{
	class MoveUpCommand final : public GameObjectCommand
	{
	public:
		MoveUpCommand() = default;

		void Execute() override;
	};

	class MoveLeftCommand final : public GameObjectCommand
	{
	public:
		MoveLeftCommand() = default;

		void Execute() override;
	};

	class MoveRightCommand final : public GameObjectCommand
	{
	public:
		MoveRightCommand() = default;

		void Execute() override;
	};

	class MoveDownCommand final : public GameObjectCommand
	{
	public:
		MoveDownCommand() = default;

		void Execute() override;
	};
}