#pragma once

// Uses statically compiled version of spdlog
#ifndef SPDLOG_COMPILED_LIB
#define SPDLOG_COMPILED_LIB
#endif  // SPDLOG_COMPILED_LIB
#include <spdlog/spdlog.h>

namespace Vulpine {
class Logger {
   public:
    static void init();
    static std::shared_ptr<spdlog::logger> getCoreLogger() {
        return s_coreLogger;
    }

   private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
};
}  // namespace Vulpine

#define VP_CORE_TRACE(...) Vulpine::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define VP_CORE_INFO(...) Vulpine::Logger::getCoreLogger()->info(__VA_ARGS__)
#define VP_CORE_WARN(...) Vulpine::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define VP_CORE_ERROR(...) Vulpine::Logger::getCoreLogger()->error(__VA_ARGS__)
#define VP_CORE_CRITICAL(...) \
    Vulpine::Logger::getCoreLogger()->critical(__VA_ARGS__)
