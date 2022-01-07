#include "Window.h"

namespace Vulpine {
Window::Window(const std::string& title, int x, int y, int w, int h,
               uint32_t flags) {
    m_Window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
}

Window::~Window() { SDL_DestroyWindow(m_Window); }
}  // namespace Vulpine