#include "Engine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <thread>

#include "Config/EngineConfig.h"
#include "Input.h"
#include "VersionConfig.h"
#include "Vulpine/Core/Logger.h"
#include "Vulpine/Managers/TextureManager.h"
#include "Vulpine/Renderer/Renderer.h"
#include "Vulpine/Scene/Scene.h"
#include "Vulpine/Utils/Clock.h"
#include "Vulpine/Utils/Utils.h"
#include "Window.h"

using namespace Vulpine::Components;

namespace Vulpine
{
Engine::Engine()
{
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

Engine::~Engine()
{
    delete m_Renderer;
    delete m_Window;
    delete m_Config;
    delete m_SceneManager;

    IMG_Quit();
    SDL_Quit();
    VP_CORE_INFO("Quitting VulpineEngine {}", VULPINE_ENGINE_VERSION);
}

int Engine::Start()
{
    m_Running = true;
    Clock::Start();
    while (m_Running)
    {
        // Update delta time before updating next frame start time
        Clock::UpdateDeltaTime();
        double start = Clock::GetElapsed<std::chrono::seconds::period>();

        Scene *current_scene = m_SceneManager->GetCurrentScene();

        Input::PollEvents();
        // Poll and handle any events we may have received from our current
        // scene.
        SceneEvents event;
        while (current_scene->PollEvents(event))
        {
            switch (event)
            {
            case SceneEvents::ENGINE_QUIT:
                m_Running = false;
                break;
            }
        }

        Vulpine::Entity *entity = current_scene->GetEntityManager().LoadEntity("data/objects/chaco-fall.obj.json");
        entity->GetComponent<Rigidbody>().velocity =
            (Vec2){Utils::RandomFloat(-200.0f, 200.0f), Utils::RandomFloat(-500.0f, -250.0f)};

        if (Input::isQuit())
            m_Running = false;
        if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE))
            m_Running = false;

        current_scene->Update();

        m_Renderer->SetColor(17, 30, 47, 0);
        m_Renderer->Clear();

        current_scene->RenderScene();

        m_Renderer->Present();

        // Pause execution for frame capping
        double end = Clock::GetElapsed<std::chrono::seconds::period>();

        // Frame sleep duration calculations.
        double secondsPerFrame = 1.0f / (double)m_Config->frames_per_second;
        double currentFrameDuration = (end - start);
        auto remainingFrameTime =
            std::chrono::duration<double, std::chrono::seconds::period>(secondsPerFrame - currentFrameDuration);

        // No system call will be called if remainingFrameTime <= 0. So we do not have to handle the case
        // where the game is running slower than the requested frame time.
        std::this_thread::sleep_for(remainingFrameTime);

        // Keep track of the engine's current frames per second.
        end = Clock::GetElapsed<std::chrono::seconds::period>();
        double frames_per_second = 1.0f / (end - start);
    }
    return 0;
}

} // namespace Vulpine