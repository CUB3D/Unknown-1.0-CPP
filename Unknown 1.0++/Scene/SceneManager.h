//
// Created by cub3d on 01/06/17.
//

#ifndef UNKNOWN_1_0_CPP_SCENEMANAGER_H
#define UNKNOWN_1_0_CPP_SCENEMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "Scene.h"

namespace Unknown
{
    class SceneManager
    {
    private:
        std::vector<std::shared_ptr<Scene>> scenes;
    public:
        std::shared_ptr<Scene> currentScene;

        SceneManager();
        ~SceneManager();
        void add(std::shared_ptr<Scene> scene);
        void loadScene(const std::string sceneName);

        const void update();

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
