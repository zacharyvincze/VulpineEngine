#include "Renderer.h"

namespace Vulpine {
Renderer::Renderer(Window& window, uint32_t flags) {
    m_Renderer = SDL_CreateRenderer(window.GetSDLWindow(), -1, flags);
}

Renderer::~Renderer() { SDL_DestroyRenderer(m_Renderer); }

void Renderer::Present() { SDL_RenderPresent(m_Renderer); }
void Renderer::Clear() { SDL_RenderClear(m_Renderer); }
void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
}
}  // namespace Vulpine