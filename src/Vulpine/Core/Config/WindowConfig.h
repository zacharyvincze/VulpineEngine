#pragma once

#include "JsonSchema.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
namespace Config {

struct WindowConfig : public JsonSchema {
    std::string title = "VulpineEngine";
    int x = 0;
    int y = 0;
    int w = 640;
    int h = 480;
    uint32_t flags = SDL_WINDOW_SHOWN;
    bool show_cursor = true;

    void ToObject(nlohmann::json& j) override;
};
}  // namespace Config
}  // namespace Vulpine