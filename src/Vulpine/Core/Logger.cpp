#include "Vulpine/Core/Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include "VersionConfig.h"

namespace Vulpine {
std::shared_ptr<spdlog::logger> Logger::s_coreLogger;

void Logger::Init() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);

    s_coreLogger = std::make_shared<spdlog::logger>("VULPINE", console_sink);
    s_coreLogger->set_level(spdlog::level::trace);
    spdlog::register_logger(s_coreLogger);
}
}  // namespace Vulpine