#pragma once
#include "Vulpine/Renderer/Renderer.h"
#include "Vulpine/Scene/Scene.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
class SceneManager {
   public:
    SceneManager(Renderer& renderer);
    ~SceneManager();
    inline Scene* GetCurrentScene() { return m_CurrentScene; }
    void SetScene(const std::string& scene_id);
    void CreateScene(const std::string& scene_id,
                     const std::string& scene_file);

   private:
    std::unordered_map<std::string, Scene*> m_Scenes;
    Scene* m_CurrentScene;

    Renderer& m_Renderer;
};
}  // namespace Vulpine