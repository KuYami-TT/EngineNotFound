#pragma once
#include <chrono>

namespace enf
{
    namespace game_time
    {
        void UpdateDelta();

        [[nodiscard]] float Delta();
        [[nodiscard]] float UnscaledDelta();
        [[nodiscard]] float FixedDelta();
        [[nodiscard]] float FPS();
        [[nodiscard]] std::chrono::duration<float, std::milli> Sleep();

        void SetScale(float timeScale = 1.);
    };
}