#include "Vulpine/vppch.h"

namespace Vulpine {
class Clock {
   public:
    static void Start();

    template <typename T>
    static unsigned long GetElapsed();

   private:
    static std::chrono::high_resolution_clock::time_point m_ClockStart;
};

template <typename T>
unsigned long Clock::GetElapsed() {
    return std::chrono::duration_cast<T>(
               std::chrono::high_resolution_clock::now() - m_ClockStart)
        .count();
}
}  // namespace Vulpine