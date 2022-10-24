#include "Engine.h"

#include <SDL2/SDL.h>

#include "Config/EngineConfig.h"
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

    // Initialize SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    // Initialize some engine related subsystems
    m_Config = new Config::EngineConfig("data/config/vulpine.json");
    m_Window = new Window(m_Config->GetWindowConfig());
    m_Renderer = new Renderer(*m_Window, m_Config->GetRenderConfig());
    m_SceneManager = new SceneManager(*m_Renderer);
}

Engine::~Engine() {
    delete m_Renderer;
    delete m_Window;
    delete m_Config;
    delete m_SceneManager;

    IMG_Quit();
    SDL_Quit();
    VP_CORE_INFO("Quitting VulpineEngine {}", VULPINE_ENGINE_VERSION);
}

int Engine::Start() {
    m_Running = true;
    Clock::Start();
    while (m_Running) {
        unsigned long start = Clock::GetElapsed<std::chrono::microseconds>();

        Scene* current_scene = m_SceneManager->GetCurrentScene();

        Input::PollEvents();
        // Poll and handle any events we may have received from our current
        // scene.
        SceneEvents event;
        while (current_scene->PollEvents(event)) {
            switch (event) {
                case SceneEvents::ENGINE_QUIT:
                    m_Running = false;
                    break;
            }
        }

        if (Input::isQuit()) m_Running = false;
        if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE)) m_Running = false;

        current_scene->Update();

        m_Renderer->SetColor(0, 0, 0, 0);
        m_Renderer->Clear();

        current_scene->RenderScene();

        m_Renderer->Present();

        // Pause execution for frame capping
        unsigned long end = Clock::GetElapsed<std::chrono::microseconds>();
        std::this_thread::sleep_for(std::chrono::microseconds((1000000 / m_Config->frames_per_second) - (end - start)));

        end = Clock::GetElapsed<std::chrono::microseconds>();
        float frames_per_second = 1000000.0f / (end - start);
    }
    return 0;
}

}  // namespace Vulpine