#include "GameTime.h"
#include <chrono>

using namespace std::chrono;

constexpr int g_FpsCap{ 16 };
double g_FixedTime{ .02 };
double g_DeltaTime{};
double g_TimeScale{ 1. };
high_resolution_clock::time_point g_LastTime = high_resolution_clock::now();
high_resolution_clock::time_point g_CurrentTime{};

void enf::game_time::UpdateDelta()
{
    g_CurrentTime = high_resolution_clock::now();
    g_DeltaTime = duration<double>(g_CurrentTime - g_LastTime).count();
    g_LastTime = g_CurrentTime;
}

double enf::game_time::Delta()
{
    return g_DeltaTime * g_TimeScale;
}

double enf::game_time::UnscaledDelta()
{
    return g_DeltaTime;
}

double enf::game_time::FixedDelta()
{
    return g_FixedTime;
}

duration<double, std::milli> enf::game_time::Sleep()
{
    return g_CurrentTime + milliseconds(g_FpsCap) - high_resolution_clock::now();
}

void enf::game_time::SetScale(double timeScale)
{
    g_TimeScale = timeScale;
}