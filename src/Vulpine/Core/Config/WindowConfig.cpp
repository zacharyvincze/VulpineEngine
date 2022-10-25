#include "WindowConfig.h"

#include <string>

namespace Vulpine
{
namespace Config
{
void WindowConfig::ToObject(nlohmann::json &j)
{
    flags = 0;

    title = j["title"].get<std::string>();
    x = j["x"].get<int>();
    y = j["y"].get<int>();
    h = j["height"].get<int>();
    w = j["width"].get<int>();

    if (j["options"]["fullscreen"].get<bool>())
    {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    else
    {
        flags |= SDL_WINDOW_SHOWN;
    }

    show_cursor = j["options"]["show_cursor"].get<bool>();
}
} // namespace Config
} // namespace Vulpine