//
// Created by cub3d on 09/12/18.
//

#include "LogViewer.h"
#include <Imgui/imgui.h>

void LogViewer::render() {
    if(!enabled)
        return;

    ImGui::SetNextWindowSize(ImVec2(500,400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Log");

    ImGui::BeginChild("Scroll", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    for(int i = 0; i < 10; i++) {
        ImGui::Text("Test");
    }

    ImGui::EndChild();

    ImGui::End();
}
