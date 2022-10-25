#pragma once

#include <SDL2/SDL.h>

#include "Vulpine/Core/Config/EngineConfig.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
class Window
{
  public:
    Window(Config::WindowConfig config);
    ~Window();
    inline SDL_Window *GetSDLWindow()
    {
        return m_Window;
    }

  private:
    SDL_Window *m_Window;
};
} // namespace Vulpine