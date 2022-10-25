#include "Vulpine/Core/Engine.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
class Clock
{
  public:
    template <typename T> static double GetElapsed();

    template <typename T> static double GetDeltaTime();

  private:
    static std::chrono::high_resolution_clock::time_point m_ClockStart;
    static std::chrono::duration<double> m_deltaTime;
    static std::chrono::high_resolution_clock::time_point m_lastDeltaTime;

    // Only the engine class should be able to access these
    static void Start();
    static void UpdateDeltaTime();

    friend class Vulpine::Engine;
};

template <typename T> double Clock::GetElapsed()
{
    auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, T> elapsed_time = current_time - m_ClockStart;
    return elapsed_time.count();
}

template <typename T> double Clock::GetDeltaTime()
{
    return std::chrono::duration<double, T>(m_deltaTime).count();
}

} // namespace Vulpine