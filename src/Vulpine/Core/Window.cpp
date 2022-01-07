#include "Window.h"

namespace Vulpine {
Window::Window(WindowConfig config) {
    m_Window = SDL_CreateWindow(config.title.c_str(), config.x, config.y,
                                config.w, config.h, config.flags);
}

Window::~Window() { SDL_DestroyWindow(m_Window); }
}  // namespace Vulpine