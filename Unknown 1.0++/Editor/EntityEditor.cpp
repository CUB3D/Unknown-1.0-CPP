//
// Created by cub3d on 16/08/18.
//

#include "EntityEditor.h"
#include "../Imgui/GUI.h"
#include "../Entity/Component.h"

Unknown::EntityEditor::EntityEditor(std::shared_ptr<::Unknown::Entity>&& ent) : ent(ent) {
    init();
}

Unknown::EntityEditor::EntityEditor(std::shared_ptr<::Unknown::Entity> &ent) : ent(ent) {
    init();
}

void Unknown::EntityEditor::populateGui() {
    this->x = ent->position.x;
    this->y = ent->position.y;
    this->angle = ent->angle;

    std::string name = "Entity##" + std::string(this->tag.data());
    ImGui::Begin(name.c_str(), nullptr);

    ImGui::InputText("Tag", tag.data(), tag.size(), ImGuiInputTextFlags_AlwaysInsertMode);

    ImGui::PushItemWidth(125);
    ImGui::InputDouble("X", &x, 0.01);
    ImGui::SameLine();
    ImGui::PushItemWidth(125);
    ImGui::InputDouble("Y", &y, 0.01);
    ImGui::InputDouble("Rotation", &angle, 0.01);
    ImGui::Spacing();

    for(auto& comp : ent->prototype.components) {
        comp->populateEditor();
        ImGui::Spacing();
    }

    ImGui::End();

    ent->setPosition(x, y, angle);
}

void Unknown::EntityEditor::init() {
    this->tag.fill(0);
    for(int i = 0; i < ent->prototype.tag.size(); i++) {
        this->tag[i] = ent->prototype.tag[i];
    }

    this->x = ent->position.x;
    this->y = ent->position.y;
    this->angle = ent->angle;
}
