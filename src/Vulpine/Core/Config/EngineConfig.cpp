#include "EngineConfig.h"

#include <SDL2/SDL.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include "Vulpine/Core/Logger.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
namespace Config
{
EngineConfig::EngineConfig(const std::string &filepath)
{
    VP_CORE_INFO("Using engine configuration file: {}", filepath);

    // Parse given JSON file
    std::ifstream in(filepath.c_str());
    if (!in.is_open())
    {
        VP_CORE_WARN("Unable to open engine configuration file {}, using defaults", filepath);
        return;
    }

    nlohmann::json in_json;
    in >> in_json;

    in.close();

    try
    {
        m_RenderConfig.ToObject(in_json.at(RENDERER_SETTINGS_KEY));
        m_WindowConfig.ToObject(in_json.at(WINDOW_SETTINGS_KEY));
    }
    catch (nlohmann::json::exception e)
    {
        VP_CORE_WARN(e.what());
    }

    frames_per_second = in_json["fps"].get<int>();
}

EngineConfig::~EngineConfig()
{
}
} // namespace Config
} // namespace Vulpine