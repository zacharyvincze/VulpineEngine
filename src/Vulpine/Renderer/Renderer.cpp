#include "Renderer.h"

namespace Vulpine {
Renderer::Renderer(Window& window, Config::RenderConfig config) {
    m_Renderer = SDL_CreateRenderer(window.GetSDLWindow(), -1, config.flags);
    SDL_RenderSetLogicalSize(m_Renderer, config.logical_width, config.logical_height);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, config.render_scale_quality.c_str());
}

Renderer::~Renderer() { SDL_DestroyRenderer(m_Renderer); }

void Renderer::Present() { SDL_RenderPresent(m_Renderer); }

void Renderer::Clear() { SDL_RenderClear(m_Renderer); }

void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { SDL_SetRenderDrawColor(m_Renderer, r, g, b, a); }

void Renderer::DrawTexture(SDL_Texture* texture, SDL_Rect* source_rect, SDL_Rect* dest_rect) {
    SDL_RenderCopy(m_Renderer, texture, source_rect, dest_rect);
}
}  // namespace Vulpine