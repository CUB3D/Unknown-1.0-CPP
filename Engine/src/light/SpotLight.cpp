//
// Created by cub3d on 19/05/2020.
//

#include "SpotLight.h"

#include <Tracy.hpp>
#include <Imgui/GUI.h>

void SpotLight::toBuffer(float *flt) const {
    ZoneScopedN("SL::ToBuffer");
    int i = 0;

    flt[i++] = position.x;
    flt[i++] = position.y;
    flt[i++] = position.z;
    flt[i++] = 0;

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

    flt[i++] = cutOff;
    flt[i++] = enabled;
    flt[i++] = 0;
    flt[i++] = 0;
}

void SpotLight::show_edit(int pos) {
    ZoneScopedN("SL::lightedit");

    char buff[100];
    snprintf(buff, sizeof(buff), "SpotLight_%i", pos);

    if(ImGui::Begin(buff)) {
        float ambient[3] = {this->ambient.x, this->ambient.y, this->ambient.z};
        float diffuse[3] = {this->diffuse.x, this->diffuse.y, this->diffuse.z};
        float specular[3] = {this->specular.x, this->specular.y, this->specular.z};
        bool enabled = this->enabled == 1.0f;

        ImGui::Text("Position");
        ImGui::SliderFloat("Pos X", &this->position.x, -1, 1);
        ImGui::SliderFloat("Pos Y", &this->position.y, -1, 1);
        ImGui::SliderFloat("Pos Z", &this->position.z, 0.01, 1);

        ImGui::Text("Direction");
        ImGui::SliderFloat("Dir X", &this->direction.x, -1, 1);
        ImGui::SliderFloat("Dir Y", &this->direction.y, -1, 1);
        ImGui::SliderFloat("Dir Z", &this->direction.z, 0.01, 1);

        ImGui::ColorEdit3("Ambient", ambient, ImGuiColorEditFlags_RGB);
        ImGui::ColorEdit3("Diffuse", diffuse, ImGuiColorEditFlags_RGB);
        ImGui::ColorEdit3("Specular", specular, ImGuiColorEditFlags_RGB);

        ImGui::SliderFloat("CutOff", &this->cutOff, 0.01, 1);

        ImGui::Checkbox("Enabled", &enabled);

        this->ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
        this->diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
        this->specular = glm::vec3(specular[0], specular[1], specular[2]);
        this->enabled = enabled ? 1.0f : 0.0f;
    }

    ImGui::End();
}


