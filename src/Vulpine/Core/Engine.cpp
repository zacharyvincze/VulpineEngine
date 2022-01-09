#include "Engine.h"

#include <SDL2/SDL.h>

#include "EngineConfig.h"
#include "VersionConfig.h"
#include "Vulpine/Core/Logger.h"
#include "Vulpine/Managers/TextureManager.h"
#include "Vulpine/Renderer/Renderer.h"
#include "Vulpine/Scene/Scene.h"
#include "Window.h"

namespace Vulpine {
Engine::Engine() {
    Logger::Init();
    VP_CORE_INFO("Starting VulpineEngine {}", VULPINE_ENGINE_VERSION);

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    EngineConfig config("data/config/vulpine.json");

    Window window = Window(config.GetWindowConfig());
    Renderer renderer = Renderer(window, config.GetRenderConfig());

    Scene scene("default", renderer.GetSDLRenderer());
    scene.Load();

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

        SDL_Rect source_rect = {0, 0, 320, 184};

        renderer.SetColor(0, 0xFF, 0, 0);
        renderer.Clear();

        scene.RenderScene();

        renderer.Present();
    }

    scene.Unload();
}
Engine::~Engine() {
    VP_CORE_INFO("Quitting VulpineEngine {}", VULPINE_ENGINE_VERSION);
}
}  // namespace Vulpine