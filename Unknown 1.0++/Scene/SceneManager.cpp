//
// Created by cub3d on 01/06/17.
//

#include "SceneManager.h"

Unknown::SceneManager::SceneManager()
{
}

Unknown::SceneManager::~SceneManager()
{
    // Delete the scenes
    for(auto& scene : this->scenes)
    {
        delete scene;
    }
}

void Unknown::SceneManager::add(Scene* scene)
{
    this->scenes.push_back(scene);
}

void Unknown::SceneManager::loadScene(const std::string sceneName)
{
    for(auto& scene : this->scenes)
    {
        if(scene->name == sceneName)
        {
            this->currentScene = scene;
            return;
        }
    }
}
