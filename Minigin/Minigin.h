#pragma once
#include <string>
#include <functional>
#include <filesystem>

namespace dae
{
	class Minigin final
	{
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		void Run(const std::function<void()>& load);
		void RunOneFrame();

	private:
		bool m_quit{};
		const int m_fps{ 16 };
		std::chrono::time_point<std::chrono::steady_clock> m_lastTime{};
	};
}