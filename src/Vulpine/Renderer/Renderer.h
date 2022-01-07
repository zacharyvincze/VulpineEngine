#pragma once

#include <SDL2/SDL.h>

#include "Vulpine/Core/EngineConfig.h"
#include "Vulpine/Core/Window.h"

namespace Vulpine {
class Renderer {
   public:
    Renderer(Window& window, RenderConfig config);
    ~Renderer();
    SDL_Renderer* GetSDLRenderer() { return m_Renderer; }

    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void Present();
    void Clear();

   private:
    SDL_Renderer* m_Renderer;
};
}  // namespace Vulpine