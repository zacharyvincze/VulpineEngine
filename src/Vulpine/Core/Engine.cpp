#include "Engine.h"

#include "VersionConfig.h"
#include "Vulpine/Core/Logger.h"

namespace Vulpine {
Engine::Engine() {
    VP_CORE_INFO("Starting VulpineEngine v{}", VULPINE_ENGINE_VERSION);
}
Engine::~Engine() {}
}  // namespace Vulpine