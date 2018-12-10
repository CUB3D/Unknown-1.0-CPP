//
// Created by cub3d on 01/06/17.
//

#include "SceneManager.h"
#include "Scene.h"
#include <Log.h>

Unknown::SceneManager::SceneManager() : currentSceneName("") {}

void Unknown::SceneManager::loadScene(const std::string& sceneName) {
    UK_LOG_INFO("Loading scene ", sceneName);

    auto sceneGenerator = sceneMapping.find(sceneName);
    if(sceneGenerator != sceneMapping.end()) {
        scenes.push_back(std::pair<std::string, std::shared_ptr<Scene>>(sceneName, sceneGenerator->second()));
        this->currentSceneName = sceneName;
        getCurrentScene()->reset();
    } else {
        UK_LOG_ERROR("Unable to load scene:", sceneName);
    }
}

const void Unknown::SceneManager::update() {
    if(getCurrentScene())
        getCurrentScene()->update();
}

void Unknown::SceneManager::loadLastScene() {
    this->scenes.pop_back();
}

const void Unknown::SceneManager::render() const {
    if(getCurrentScene())
        getCurrentScene()->render();
}

const void Unknown::SceneManager::reset() {
    getCurrentScene()->reset();
}

std::shared_ptr<Unknown::Scene> Unknown::SceneManager::getCurrentScene() const {
    return scenes.back().second;
}

const std::unordered_set<std::string> Unknown::SceneManager::getAvailableScenes() const {
    std::unordered_set<std::string> keys;

    for(auto&& elements : this->sceneMapping)
        keys.insert(elements.first);

    return keys;
}

const std::string Unknown::SceneManager::getCurrentSceneName() const {
    return scenes.back().first;
}
