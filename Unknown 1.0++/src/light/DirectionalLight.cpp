//
// Created by cub3d on 18/05/2020.
//

#include "DirectionalLight.h"
#include <Tracy.hpp>
#include <Imgui/GUI.h>

void DirectionalLight::toBuffer(float *flt) const {
    ZoneScopedN("DL::ToBuffer");
    int i = 0;

    flt[i++] = direction.x;
    flt[i++] = direction.y;
    flt[i++] = direction.z;
    flt[i++] = 0;


    flt[i++] = ambient.x;
    flt[i++] = ambient.y;
    flt[i++] = ambient.z;
    flt[i++] = 0;

    flt[i++] = diffuse.x;
    flt[i++] = diffuse.y;
    flt[i++] = diffuse.z;
    flt[i++] = 0;

    flt[i++] = specular.x;
    flt[i++] = specular.y;
    flt[i++] = specular.z;
    flt[i++] = 0;

    flt[i++] = enabled;
    flt[i++] = 0;
    flt[i++] = 0;
    flt[i++] = 0;
}

void DirectionalLight::show_edit(int pos) {
    ZoneScopedN("DL::lightedit");

    char buff[100];
    snprintf(buff, sizeof(buff), "DirectionLight_%i", pos);

    if(ImGui::Begin(buff)) {
        float ambient[3] = {this->ambient.x, this->ambient.y, this->ambient.z};
        float diffuse[3] = {this->diffuse.x, this->diffuse.y, this->diffuse.z};
        float specular[3] = {this->specular.x, this->specular.y, this->specular.z};
        bool enabled = this->enabled == 1.0f;

        ImGui::SliderFloat("X", &this->direction.x, -1, 1);
        ImGui::SliderFloat("Y", &this->direction.y, -1, 1);

        ImGui::ColorEdit3("Ambient", ambient, ImGuiColorEditFlags_RGB);
        ImGui::ColorEdit3("Diffuse", diffuse, ImGuiColorEditFlags_RGB);
        ImGui::ColorEdit3("Specular", specular, ImGuiColorEditFlags_RGB);
        ImGui::Checkbox("Enabled", &enabled);

        this->ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
        this->diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
        this->specular = glm::vec3(specular[0], specular[1], specular[2]);

        this->enabled = enabled ? 1.0f : 0.0f;
    }

    ImGui::End();
}

