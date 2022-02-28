#include "Clock.h"

namespace Vulpine {

std::chrono::high_resolution_clock::time_point Clock::m_ClockStart;

void Clock::Start() {
    m_ClockStart = std::chrono::high_resolution_clock::now();
}
}  // namespace Vulpine