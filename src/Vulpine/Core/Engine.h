#ifndef ENGINE_H
#define ENGINE_H

#include "Vulpine/Core/Config/EngineConfig.h"
#include "Vulpine/Managers/SceneManager.h"

namespace Vulpine {
class Engine {
   public:
    Engine();
    ~Engine();

    int Start();

    SceneManager* GetSceneManager() { return m_SceneManager; }

   private:
    SceneManager* m_SceneManager;

    bool m_Running;

    Window* m_Window;
    Renderer* m_Renderer;
    Config::EngineConfig* m_Config;
};
}  // namespace Vulpine

#endif  // ENGINE_H