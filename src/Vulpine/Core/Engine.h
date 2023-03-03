#ifndef ENGINE_H
#define ENGINE_H

#include "Vulpine/Core/Config/EngineConfig.h"
#include "Vulpine/Managers/SceneManager.h"

namespace Vulpine
{
/**
 * @brief Main engine instance.
 *
 */
class Engine
{
  public:
    Engine();
    ~Engine();

    /**
     * @brief Initializes the game engine and starts the main loop.
     *
     * @return 0 if the engine has initialized successfully. < 0 otherwise.
     */
    int Start();

    SceneManager *GetSceneManager()
    {
        return m_SceneManager;
    }

  private:
    void Loop();
    void Input();
    void Update();
    void Render();
    void CapFramerate();

    SceneManager *m_SceneManager;

    bool m_Running;

    Window *m_Window;
    Renderer *m_Renderer;
    Config::EngineConfig *m_Config;
};
} // namespace Vulpine

#endif // ENGINE_H