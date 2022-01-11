#include "Vulpine/vppch.h"

namespace Vulpine {
class Clock {
   public:
    inline void Start() {
        m_ClockStart = std::chrono::high_resolution_clock::now();
    }

    template <typename T>
    unsigned long GetElapsed() {
        return std::chrono::duration_cast<T>(
                   std::chrono::high_resolution_clock::now() - m_ClockStart)
            .count();
    }

   private:
    std::chrono::high_resolution_clock::time_point m_ClockStart;
};
}  // namespace Vulpine