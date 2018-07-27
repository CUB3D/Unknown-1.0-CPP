//
// Created by cub3d on 01/06/17.
//
#include "../stdafx.h"

#include "SceneManager.h"
#include "Scene.h"

Unknown::SceneManager::SceneManager() : currentSceneName("")
{
}

Unknown::SceneManager::~SceneManager()
{
    // Delete the scenes
//    for(auto& scene : this->scenes)
//    {
//        delete scene;
//    }
}

void Unknown::SceneManager::add(std::shared_ptr<Scene> scene)
{
    this->scenes[scene->name] = scene;
}

void Unknown::SceneManager::loadScene(const std::string sceneName)
{
    //TODO: error checking
    this->currentSceneName = sceneName;
    this->currentScene = this->scenes[sceneName];
    this->sceneHistory.push(sceneName);
}

const void Unknown::SceneManager::update()
{
    if(this->currentScene)
        this->currentScene->update();
}

void Unknown::SceneManager::loadLastScene() {
    this->sceneHistory.pop();
    this->currentScene = this->scenes[this->sceneHistory.top()];
}

const void Unknown::SceneManager::render() const {
    if(this->currentScene)
        this->currentScene->render();
}
