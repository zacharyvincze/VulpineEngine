#pragma once

#include "Vulpine/Core/Config/JsonSchema.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
namespace Config {
struct RenderConfig : public JsonSchema {
    int logical_width = 640;
    int logical_height = 480;
    uint32_t flags = SDL_RENDERER_SOFTWARE;
    std::string render_scale_quality = "1";

    void ToObject(nlohmann::json& j) override;
};
}  // namespace Config
}  // namespace Vulpine