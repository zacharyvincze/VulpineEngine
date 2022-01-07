#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {

struct RenderConfig {
    int logical_width, logical_height;
    uint32_t flags;
};

struct WindowConfig {
    std::string title;
    int x, y, w, h;
    uint32_t flags;
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

    void SetRenderConfigDefaults();
    void SetWindowConfigDefaults();

    RenderConfig m_RenderConfig;
    WindowConfig m_WindowConfig;
};
}  // namespace Vulpine