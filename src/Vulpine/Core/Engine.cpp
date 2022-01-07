#include "Engine.h"

#include <SDL2/SDL.h>

#include "VersionConfig.h"
#include "Vulpine/Core/Logger.h"
#include "Vulpine/Renderer/Renderer.h"
#include "Window.h"

namespace Vulpine {
Engine::Engine() {
    Logger::Init();
    VP_CORE_INFO("Starting VulpineEngine {}", VULPINE_ENGINE_VERSION);

    Window window = Window("VulpineEngine", SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    Renderer renderer =
        Renderer(window, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        running = false;
                        break;
                }
            }

            else if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer.SetColor(0xFF, 0, 0, 0);
        renderer.Clear();

        renderer.Present();
    }
}
Engine::~Engine() {
    VP_CORE_INFO("Quitting VulpineEngine {}", VULPINE_ENGINE_VERSION);
}
}  // namespace Vulpine