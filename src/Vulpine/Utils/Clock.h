#include "Vulpine/vppch.h"

namespace Vulpine {
class Clock {
   public:
    static void Start();

    template <typename T>
    static double GetElapsed();

    template <typename T>
    static double GetDeltaTime();

    static void UpdateDeltaTime();

   private:
    static std::chrono::high_resolution_clock::time_point m_ClockStart;
    static std::chrono::duration<double> m_deltaTime;
    static std::chrono::high_resolution_clock::time_point m_lastDeltaTime;
};

template <typename T>
double Clock::GetElapsed() {
    auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, T> elapsed_time = current_time - m_ClockStart;
    return elapsed_time.count();
}

template <typename T>
double Clock::GetDeltaTime() {
    return std::chrono::duration<double, T>(m_deltaTime).count();
}

}  // namespace Vulpine