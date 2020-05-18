//
// Created by cub3d on 18/05/2020.
//

#include "LightingManager2D.h"

LightingManager2D::LightingManager2D()  {
    lightBuffer = static_cast<float *>(malloc(POINT_SIZE * sizeof(float)));

    for(int i = 0; i < POINT_SIZE; i++) {
        lightBuffer[i] = 0;
    }
}

void LightingManager2D::init() {
    glGenBuffers(1, &lightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    glBufferData(GL_UNIFORM_BUFFER, POINT_SIZE, &lightBuffer[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    updateLightBuffer();
    updateBuffer();
}

void LightingManager2D::updateBuffer() {
    ZoneScopedN("R2D::buffer bind");
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    void* map = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(map, &lightBuffer[0], POINT_SIZE * sizeof(float));
    glUnmapBuffer(GL_UNIFORM_BUFFER);
}

void LightingManager2D::updateLightBuffer() {
    ZoneScopedN("R2D::light to buffer");
    for (int i = 0; i < lights.size(); i++) {
        lights[i]->show_edit(i);
        lights[i]->toBuffer(&lightBuffer[i * POINT_SIZE]);
    }

    if(ImGui::Begin("Light buffer")) {
        ImGui::Columns(4, "Buffer", true);
        for(int i = 0; i < 4; i++) {
            for (int j = 0; j < POINT_SIZE / 4; j++) {
                ImGui::Text("%f", lightBuffer[j * 4 + i]);
            }
            ImGui::NextColumn();
        }
        ImGui::NextColumn();
    }
    ImGui::End();
}

void LightingManager2D::bindBuffer(int index) {
    glBindBufferBase(GL_UNIFORM_BUFFER, index, lightUBO);
}
