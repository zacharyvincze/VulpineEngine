#include "Engine.h"

#include <SDL2/SDL.h>

#include "EngineConfig.h"
#include "Input.h"
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

    m_SceneManager = new SceneManager(renderer);
    m_SceneManager->CreateScene("default", "data/scenes/default.scene.json");
    m_SceneManager->SetScene("default");

    bool running = true;
    SDL_Event event;

    unsigned long time_per_frame = 1000000 / config.frames_per_second;
    m_Clock.Start();

    while (running) {
        unsigned long start = m_Clock.GetElapsed<std::chrono::microseconds>();

        Scene* current_scene = m_SceneManager->GetCurrentScene();

        Input::PollEvents();
        // Poll and handle any events we may have received from our current
        // scene.
        SceneEvents event;
        while (current_scene->PollEvents(event)) {
            switch (event) {
                case SceneEvents::ENGINE_QUIT:
                    running = false;
                    break;
            }
        }

        if (Input::isQuit()) running = false;
        if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE)) running = false;

        current_scene->Update();

        renderer.SetColor(0, 0, 0, 0);
        renderer.Clear();

        current_scene->RenderScene();

        renderer.Present();

        // Pause execution for frame capping
        unsigned long end = m_Clock.GetElapsed<std::chrono::microseconds>();
        std::this_thread::sleep_for(
            std::chrono::microseconds(time_per_frame - (end - start)));

        end = m_Clock.GetElapsed<std::chrono::microseconds>();
        float frames_per_second = 1000000.0f / (end - start);
    }

    delete m_SceneManager;
}
Engine::~Engine() {
    VP_CORE_INFO("Quitting VulpineEngine {}", VULPINE_ENGINE_VERSION);
}
}  // namespace Vulpine