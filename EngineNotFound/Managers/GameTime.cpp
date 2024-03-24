#include "GameTime.h"
#include <chrono>

using namespace std::chrono;

constexpr milliseconds g_MsPerFrame{ 16 };
float g_FixedTime{ .02f };
float g_DeltaTime{};
float g_TimeScale{ 1.f };
high_resolution_clock::time_point g_LastTime = high_resolution_clock::now();
high_resolution_clock::time_point g_CurrentTime{};

void enf::game_time::UpdateDelta()
{
    g_CurrentTime = high_resolution_clock::now();
    g_DeltaTime = duration<float>(g_CurrentTime - g_LastTime).count();
    g_LastTime = g_CurrentTime;
}

float enf::game_time::Delta()
{
    if (g_DeltaTime > 1)
        g_DeltaTime = 1;

    return g_DeltaTime * g_TimeScale;
}

float enf::game_time::UnscaledDelta()
{
    return g_DeltaTime;
}

float enf::game_time::FixedDelta()
{
    return g_FixedTime;
}

float enf::game_time::FPS()
{
    return 1 / g_DeltaTime;
}

duration<float, std::milli> enf::game_time::Sleep()
{
    return g_CurrentTime + g_MsPerFrame - high_resolution_clock::now();
}

void enf::game_time::SetScale(float timeScale)
{
    g_TimeScale = timeScale;
}