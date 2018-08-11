//
// Created by cub3d on 01/06/17.
//

#ifndef UNKNOWN_1_0_CPP_SCENEMANAGER_H
#define UNKNOWN_1_0_CPP_SCENEMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <map>

namespace Unknown
{
    class Scene;

    class SceneManager
    {
    private:
        std::map<std::string, std::shared_ptr<Scene>>& getSceneMap() const;
    public:
        std::string currentSceneName;
        std::shared_ptr<Scene> currentScene;
        std::stack<std::string> sceneHistory;

        SceneManager();
        ~SceneManager();
        void add(std::shared_ptr<Scene> scene);
        void loadScene(const std::string sceneName);
        void loadLastScene();

        const void update();
        const void render() const;

        template<class T>
        std::shared_ptr<T> getScene()
        {
            return std::dynamic_pointer_cast<T>(this->currentScene);
        }

        SceneManager(const SceneManager& sm) = delete;
        SceneManager& operator=(const SceneManager& sm) = delete;
    };
}


#endif //UNKNOWN_1_0_CPP_SCENEMANAGER_H
