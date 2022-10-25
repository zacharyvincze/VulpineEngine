#include "Clock.h"

namespace Vulpine
{

std::chrono::high_resolution_clock::time_point Clock::m_ClockStart;
std::chrono::high_resolution_clock::time_point Clock::m_lastDeltaTime;
std::chrono::duration<double> Clock::m_deltaTime;

void Clock::UpdateDeltaTime()
{
    std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
    m_deltaTime = current_time - m_lastDeltaTime;
    m_lastDeltaTime = current_time;
}

void Clock::Start()
{
    m_ClockStart = std::chrono::high_resolution_clock::now();
    m_lastDeltaTime = m_ClockStart;
}
} // namespace Vulpine