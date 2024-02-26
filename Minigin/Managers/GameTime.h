#pragma once
#include <chrono>

namespace enf
{
    namespace game_time
    {
        void UpdateDelta();

        [[nodiscard]] double Delta();
        [[nodiscard]] double UnscaledDelta();
        [[nodiscard]] double FixedDelta();
        [[nodiscard]] double FPS();
        [[nodiscard]] std::chrono::duration<double, std::milli> Sleep();

        void SetScale(double timeScale = 1.);
    };
}