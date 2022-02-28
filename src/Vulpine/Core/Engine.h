#ifndef ENGINE_H
#define ENGINE_H

#include "Vulpine/Core/EngineConfig.h"
#include "Vulpine/Managers/SceneManager.h"
#include "Vulpine/Utils/Clock.h"

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
    EngineConfig* m_Config;
};
}  // namespace Vulpine

#endif  // ENGINE_H