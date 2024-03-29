#pragma once

#include <functional>
#include <filesystem>

#include "InputMap.h"

namespace enf
{
	class Minigin final
	{
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();

		Minigin(Minigin&& other) = delete;
		Minigin(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;

		void Run(const std::function<void()>& load);
		void RunOneFrame();

	private:
		bool m_Quit{};
		double m_Lag{};
	};
}
