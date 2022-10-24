#include "RenderConfig.h"

namespace Vulpine {
namespace Config {
void RenderConfig::ToObject(nlohmann::json& j) {
    logical_height = j["height"].get<int>();
    logical_width = j["width"].get<int>();
    flags = 0;

    if (j["options"]["accelerated"].get<bool>()) flags |= SDL_RENDERER_ACCELERATED;
    if (j["options"]["vertical-sync"].get<bool>()) flags |= SDL_RENDERER_PRESENTVSYNC;
    render_scale_quality = j["options"]["scale_quality"].get<std::string>();
}
}  // namespace Config
}  // namespace Vulpine