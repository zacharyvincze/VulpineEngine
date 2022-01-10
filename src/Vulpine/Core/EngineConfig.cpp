#include "EngineConfig.h"

#include <SDL2/SDL.h>

#include "Logger.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
EngineConfig::EngineConfig(const std::string& filepath) {
    VP_CORE_INFO("Using engine configuration file: {}", filepath);

    // Parse given JSON file
    std::ifstream in(filepath.c_str());
    if (!in.is_open()) {
        VP_CORE_WARN(
            "Unable to open engine configuration file {}, using defaults",
            filepath);
        return;
    }

    nlohmann::json in_json;
    in >> in_json;

    in.close();

    ParseRenderConfig(in_json["renderer"]);
    ParseWindowConfig(in_json["window"]);
    frames_per_second = in_json["fps"].get<int>();
}

void EngineConfig::ParseRenderConfig(nlohmann::json& json) {
    if (json.is_null()) {
        VP_CORE_WARN("Unable to read render config, using defaults");
        return;
    }

    m_RenderConfig.logical_height = json["height"].get<int>();
    m_RenderConfig.logical_width = json["width"].get<int>();
    m_RenderConfig.flags = 0;

    if (json["options"]["accelerated"].get<bool>())
        m_RenderConfig.flags |= SDL_RENDERER_ACCELERATED;
    if (json["options"]["vertical-sync"].get<bool>())
        m_RenderConfig.flags |= SDL_RENDERER_PRESENTVSYNC;
    m_RenderConfig.render_scale_quality =
        json["options"]["scale_quality"].get<std::string>();
}

void EngineConfig::ParseWindowConfig(nlohmann::json& json) {
    if (json.is_null()) {
        VP_CORE_WARN("Unable to read window config, using defaults");
        return;
    }

    m_WindowConfig.flags = 0;

    m_WindowConfig.title = json["title"].get<std::string>();
    m_WindowConfig.x = json["x"].get<int>();
    m_WindowConfig.y = json["y"].get<int>();
    m_WindowConfig.h = json["height"].get<int>();
    m_WindowConfig.w = json["width"].get<int>();

    if (json["options"]["fullscreen"].get<bool>()) {
        m_WindowConfig.flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else {
        m_WindowConfig.flags |= SDL_WINDOW_SHOWN;
    }

    m_WindowConfig.show_cursor = json["options"]["show_cursor"].get<bool>();
}

EngineConfig::~EngineConfig() {}
}  // namespace Vulpine