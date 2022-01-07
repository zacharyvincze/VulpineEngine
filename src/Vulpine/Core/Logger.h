#pragma once

// Uses statically compiled version of spdlog
#ifndef SPDLOG_COMPILED_LIB
#define SPDLOG_COMPILED_LIB
#endif  // SPDLOG_COMPILED_LIB
#include <spdlog/spdlog.h>

namespace Vulpine {

/**
 * @brief Responsible for logging engine messages at varying levels.
 *
 */
class Logger {
   public:
    static void Init();
    static std::shared_ptr<spdlog::logger> GetCoreLogger() {
        return s_coreLogger;
    }

   private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
};
}  // namespace Vulpine

#define VP_CORE_TRACE(...) Vulpine::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define VP_CORE_INFO(...) Vulpine::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define VP_CORE_WARN(...) Vulpine::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define VP_CORE_ERROR(...) Vulpine::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define VP_CORE_CRITICAL(...) \
    Vulpine::Logger::GetCoreLogger()->critical(__VA_ARGS__)
