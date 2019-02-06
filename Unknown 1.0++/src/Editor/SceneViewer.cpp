//
// Created by cub3d on 09/12/18.
//

#include "SceneViewer.h"
#include <Unknown.h>
#include <memory>
#include <Scene/Scene.h>
#include <Scene/SceneManager.h>

void Unknown::SceneViewer::render() {
    if(!enabled)
        return;

    ImGui::SetNextWindowSize(ImVec2(200,400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Scenes");

    auto& sceneManager = getUnknown().globalSceneManager;



    // Draw list of available scenes
    int i = 0;
    // Convert scene names (set<std::string>) to a char**
    auto sceneNames = sceneManager.getAvailableScenes();
    const char** scenes = new const char*[sceneNames.size()];
    for(auto&& s : sceneNames) {
        if(s == sceneManager.currentSceneName) {
            selectedScene = i;
        }

        scenes[i++] = s.c_str();
    }

    if(ImGui::ListBox("Scenes", &selectedScene, scenes, i)) {
        sceneManager.loadScene(std::string(scenes[selectedScene]));
    }
    free(scenes);



    // Button to reset current scene
    if(ImGui::Button("Reset")) {
        sceneManager.reset();
    }



    int current = -1;
    scenes = new const char*[sceneManager.scenes.size()];
    for(auto&& s : sceneManager.scenes) {
        scenes[++current] = s.first.c_str();
    }

    // Scene history
    ImGui::ListBox("Scene History", &current, scenes, current+1);
    free(scenes);

    if(ImGui::Button("^")) {
        sceneManager.loadLastScene();
    }

    ImGui::End();
}
