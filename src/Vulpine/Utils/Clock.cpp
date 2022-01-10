#include "Clock.h"

namespace Vulpine {
void Clock::Start() {
    m_ClockStart = std::chrono::high_resolution_clock::now();
}
}  // namespace Vulpine