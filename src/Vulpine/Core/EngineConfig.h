#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {

struct RenderConfig {
    int logical_width = 640;
    int logical_height = 480;
    uint32_t flags = SDL_RENDERER_SOFTWARE;
    std::string render_scale_quality = "1";
};

struct WindowConfig {
    std::string title = "VulpineEngine";
    int x = 0;
    int y = 0;
    int w = 640;
    int h = 480;
    uint32_t flags = SDL_WINDOW_SHOWN;
    bool show_cursor = true;
};

/**
 * @brief Reads Vulpine engine configuration files.
 *
 */
class EngineConfig {
   public:
    EngineConfig(const std::string& filepath);
    ~EngineConfig();

    inline RenderConfig GetRenderConfig() { return m_RenderConfig; }
    inline WindowConfig GetWindowConfig() { return m_WindowConfig; }

   private:
    void ParseRenderConfig(nlohmann::json& render_json);
    void ParseWindowConfig(nlohmann::json& window_json);

    RenderConfig m_RenderConfig;
    WindowConfig m_WindowConfig;
};
}  // namespace Vulpine