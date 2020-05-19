//
// Created by cub3d on 18/05/2020.
//

#include "LightingManager2D.h"

LightingManager2D::LightingManager2D()  {
    lightBuffer = static_cast<float *>(malloc(LIGHT_BUFFER_SIZE * sizeof(float)));

    for(int i = 0; i < LIGHT_BUFFER_SIZE; i++) {
        lightBuffer[i] = 0;
    }
}

void LightingManager2D::init() {
    glGenBuffers(1, &lightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    glBufferData(GL_UNIFORM_BUFFER, LIGHT_BUFFER_SIZE, &lightBuffer[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    updateLightBuffer();
    updateBuffer();
}

void LightingManager2D::updateBuffer() {
    ZoneScopedN("LM::buffer bind");
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    void* map = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(map, &lightBuffer[0], LIGHT_BUFFER_SIZE * sizeof(float));
    glUnmapBuffer(GL_UNIFORM_BUFFER);
}

void LightingManager2D::updateLightBuffer() {
    ZoneScopedN("LM::light to buffer");
    for (int i = 0; i < pointLights.size(); i++) {
        pointLights[i]->show_edit(i);
        pointLights[i]->toBuffer(&lightBuffer[i * PointLight::BUFFER_SIZE]);
    }
//    for (int i = 0; i < directionalLights.size(); i++) {
//        directionalLights[i]->show_edit(i);
//        directionalLights[i]->toBuffer(&lightBuffer[POINT_SIZE + i * DirectionalLight::BUFFER_SIZE]);
//    }

    if(ImGui::Begin("Light buffer")) {
        ImGui::Columns(8, "Buffer", true);
        for(int i = 0; i < 8; i++) {
            for (int j = 0; j < LIGHT_BUFFER_SIZE / 8; j++) {
                ImGui::Text("%f", lightBuffer[j * 8 + i]);
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
