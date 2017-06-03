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
        std::vector<Scene*> scenes;
    public:
        Scene* currentScene;

        SceneManager();
        ~SceneManager();
        void add(Scene* scene);
        void loadScene(const std::string sceneName);

        template<class T>
        T* getScene()
        {
            return (T*) this->currentScene;
        }

        SceneManager(const SceneManager& sm) = delete;
        SceneManager& operator=(const SceneManager& sm) = delete;
    };
}


#endif //UNKNOWN_1_0_CPP_SCENEMANAGER_H
