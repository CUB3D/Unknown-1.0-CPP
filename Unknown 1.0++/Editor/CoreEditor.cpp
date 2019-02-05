//
// Created by cub3d on 09/12/18.
//

#include "CoreEditor.h"
#include <Imgui/imgui.h>

#include "LogViewer.h"
#include "SceneViewer.h"
#include "FileSystemViewer.h"

void CoreEditor::render() {
    using namespace Unknown;

    if(ImGui::BeginMainMenuBar()) {

        if(ImGui::BeginMenu("View")) {
            ImGui::Checkbox("Log", &LogViewer::getInstance().enabled);
            ImGui::Checkbox("Scenes", &SceneViewer::getInstance().enabled);
            ImGui::Checkbox("Files", &FileSystemViewer::getInstance().enabled);

            ImGui::EndMenu();
        }


        ImGui::EndMainMenuBar();
    }

    LogViewer::getInstance().render();
    SceneViewer::getInstance().render();
    FileSystemViewer::getInstance().render();
}

void CoreEditor::update() {

}