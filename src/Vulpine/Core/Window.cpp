#include "Window.h"

namespace Vulpine
{
Window::Window(Config::WindowConfig config)
{
    m_Window = SDL_CreateWindow(config.title.c_str(), config.x, config.y, config.w, config.h, config.flags);
    SDL_ShowCursor(config.show_cursor);
}

Window::~Window()
{
    SDL_DestroyWindow(m_Window);
}
} // namespace Vulpine