//
// Created by cub3d on 01/06/17.
//
#include "../stdafx.h"

#include "SceneManager.h"
#include "Scene.h"
#include "../Log.h"

Unknown::SceneManager::SceneManager() : currentSceneName(""), currentScene(nullptr)
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
    if(!scene) {
        UK_LOG_ERROR("Attempt to register null scene");
    }

    this->getSceneMap()[scene->name] = scene;
}

void Unknown::SceneManager::loadScene(const std::string sceneName)
{
    UK_LOG_INFO("Loading scene ", sceneName);

    //TODO: error checking
    this->currentSceneName = sceneName;
    this->currentScene = this->getSceneMap()[sceneName];
    this->sceneHistory.push(sceneName);
}

const void Unknown::SceneManager::update()
{
    if(this->currentScene)
        this->currentScene->update();
}

void Unknown::SceneManager::loadLastScene() {
    this->sceneHistory.pop();
    this->currentScene = this->getSceneMap()[this->sceneHistory.top()];
}

const void Unknown::SceneManager::render() const {
    if(this->currentScene)
        this->currentScene->render();
}

std::map<std::string, std::shared_ptr<Unknown::Scene>> &Unknown::SceneManager::getSceneMap() const {
    static std::map<std::string, std::shared_ptr<Scene>> scenes;
    return scenes;
}
