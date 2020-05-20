//
// Created by cub3d on 16/12/18.
//

#include "FileSystemViewer.h"

void FileSystemViewer::render() {
    if(!enabled)
        return;

    ImGui::Begin("Files");
    ImGui::Text("Files");

    if(ImGui::CollapsingHeader("Files")) {
        if(ImGui::TreeNode("File1"))
            ImGui::TreeNode("File2");
    }

    ImGui::End();

    ImGui::ShowDemoWindow();
}
