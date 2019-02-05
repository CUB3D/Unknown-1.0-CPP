//
// Created by cub3d on 01/06/17.
//

#ifndef UNKNOWN_1_0_CPP_SCENEMANAGER_H
#define UNKNOWN_1_0_CPP_SCENEMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <memory>
#include <functional>
#include <map>
#include <unordered_set>

namespace Unknown {
    class Scene;

    class SceneManager {
    public:
        //name : generator
        std::map<std::string, std::function<std::shared_ptr<Scene>(void)>> sceneMapping;
        std::vector<std::pair<std::string, std::shared_ptr<Scene>>> scenes;
    public:
        std::string currentSceneName;

        SceneManager();
        void loadScene(const std::string& sceneName);
        void loadLastScene();

        template<class T>
        void registerScene(const std::string name) {
            sceneMapping[name] = []() {
                return std::make_shared<T>();
            };
        }

        const void update();
        const void render() const;
        const void reset();

        const std::unordered_set<std::string> getAvailableScenes() const;

        template<class T>
        std::shared_ptr<T> getScene() {
            return std::dynamic_pointer_cast<T>(getCurrentScene());
        }
        std::shared_ptr<Scene> getCurrentScene() const;
        const std::string getCurrentSceneName() const;

        SceneManager(const SceneManager& sm) = delete;
        SceneManager& operator=(const SceneManager& sm) = delete;
    };
}


#endif //UNKNOWN_1_0_CPP_SCENEMANAGER_H
