#pragma once

#include <SDL2/SDL.h>

#include <string>

namespace Vulpine {
class Window {
   public:
    Window(const std::string& title, int x, int y, int w, int h,
           uint32_t flags);
    ~Window();
    inline SDL_Window* GetSDLWindow() { return m_Window; }

   private:
    SDL_Window* m_Window;
};
}  // namespace Vulpine