//
// Created by cub3d on 01/06/17.
//

#include "SceneManager.h"
#include "Scene.h"
#include <Log.h>

Unknown::SceneManager::SceneManager() : currentSceneName(""), currentScene(nullptr) {}

void Unknown::SceneManager::add(std::shared_ptr<Scene> scene)
{
    if(!scene) {
        UK_LOG_ERROR("Attempt to register null scene");
    }

    scenes[scene->name] = scene;
}

void Unknown::SceneManager::loadScene(const std::string sceneName)
{
    UK_LOG_INFO("Loading scene ", sceneName);

    //TODO: error checking
    this->currentSceneName = sceneName;
    this->currentScene = scenes[sceneName];
    this->sceneHistory.push_back(sceneName);
}

const void Unknown::SceneManager::update()
{
    if(this->currentScene)
        this->currentScene->update();
}

void Unknown::SceneManager::loadLastScene() {
    this->sceneHistory.pop_back();
    this->currentScene = scenes[this->sceneHistory[this->sceneHistory.size()]];
}

const void Unknown::SceneManager::render() const {
    if(this->currentScene)
        this->currentScene->render();
}
