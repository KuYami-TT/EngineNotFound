#pragma once
#include "GameObjectCommand.h"

namespace enf
{
	class TakeDamageCommand final : public GameObjectCommand
	{
	public:
		TakeDamageCommand() = default;
		void Execute() override;
	};

	class GetPointsCommand final : public GameObjectCommand
	{
	public:
		inline GetPointsCommand(int points) : m_Points{ points }{}
		void Execute() override;

	private:
		int m_Points{};
	};
}
