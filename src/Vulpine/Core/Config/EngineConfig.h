#pragma once

#include "Vulpine/Core/Config/RenderConfig.h"
#include "Vulpine/Core/Config/WindowConfig.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
namespace Config
{

/**
 * @brief Reads Vulpine engine configuration files.
 *
 */
class EngineConfig
{
  public:
    EngineConfig(const std::string &filepath);
    ~EngineConfig();

    // Config for engine-specific submodules
    inline RenderConfig GetRenderConfig()
    {
        return m_RenderConfig;
    }
    inline WindowConfig GetWindowConfig()
    {
        return m_WindowConfig;
    }

    int frames_per_second = 0;

  private:
    const std::string RENDERER_SETTINGS_KEY = "renderer";
    const std::string WINDOW_SETTINGS_KEY = "window";

    RenderConfig m_RenderConfig;
    WindowConfig m_WindowConfig;
};

} // namespace Config
} // namespace Vulpine