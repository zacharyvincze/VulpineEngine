#include "SceneManager.h"

namespace Vulpine {
SceneManager::SceneManager(Renderer& renderer) : m_Renderer(renderer) {
    m_CurrentScene = NULL;
}

SceneManager::~SceneManager() {
    for (std::pair<std::string, Scene*> scene : m_Scenes) {
        scene.second->Unload();
        delete scene.second;
    }

    m_Scenes.clear();
}

Scene* SceneManager::CreateScene(const std::string& scene_id,
                                 const std::string& scene_file) {
    Scene* scene = new Scene(scene_id, scene_file, m_Renderer);
    m_Scenes.insert(std::pair<std::string, Scene*>(scene_id, scene));
    VP_CORE_DEBUG("Created scene {}", scene_id);
    return scene;
}

void SceneManager::SetScene(const std::string& scene_id) {
    if (m_CurrentScene != NULL) {
        m_CurrentScene->Unload();
    }

    if (m_Scenes.count(scene_id) == 0) {
        VP_CORE_ERROR("Scene {} does not exist", scene_id);
    }

    m_CurrentScene = m_Scenes.at(scene_id);

    m_CurrentScene->Load();

    VP_CORE_DEBUG("Switched to scene {}", scene_id);
}
}  // namespace Vulpine