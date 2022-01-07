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
        SetWindowConfigDefaults();
        SetRenderConfigDefaults();
        return;
    }

    nlohmann::json in_json;
    in >> in_json;

    in.close();

    ParseRenderConfig(in_json["renderer"]);
    ParseWindowConfig(in_json["window"]);
}

void EngineConfig::ParseRenderConfig(nlohmann::json& json) {
    if (json.is_null()) {
        VP_CORE_WARN("Unable to read render config, using defaults");
        SetRenderConfigDefaults();
        return;
    }

    m_RenderConfig.logical_height = json["height"].get<int>();
    m_RenderConfig.logical_width = json["width"].get<int>();
    m_RenderConfig.flags = 0;

    if (json["options"]["accelerated"].get<bool>())
        m_RenderConfig.flags |= SDL_RENDERER_ACCELERATED;
    if (json["options"]["vertical-sync"].get<bool>())
        m_RenderConfig.flags |= SDL_RENDERER_PRESENTVSYNC;
}

void EngineConfig::ParseWindowConfig(nlohmann::json& json) {
    if (json.is_null()) {
        VP_CORE_WARN("Unable to read window config, using defaults");
        SetWindowConfigDefaults();
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
}

void EngineConfig::SetRenderConfigDefaults() {
    m_RenderConfig = {640, 480, SDL_RENDERER_SOFTWARE};
}

void EngineConfig::SetWindowConfigDefaults() {
    m_WindowConfig = {"VulpineEngine", 0, 0, 640, 480, SDL_WINDOW_SHOWN};
}

EngineConfig::~EngineConfig() {}
}  // namespace Vulpine