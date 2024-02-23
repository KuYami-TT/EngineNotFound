#pragma once
#include <chrono>

namespace dae
{
    namespace game_time
    {
        void UpdateDelta();

        [[nodiscard]] double Delta();
        [[nodiscard]] double UnscaledDelta();
        [[nodiscard]] double FixedDelta();
        [[nodiscard]] std::chrono::duration<double, std::milli> Sleep();

        void SetScale(double timeScale = 1.);
    };
}