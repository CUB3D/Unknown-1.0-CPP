//
// Created by cub3d on 29/07/2018.
//

#include "BasicRenderComponent.h"
#include <UI2D.h>
#include <Imgui/GUI.h>
#include <Entity/Entity.h>


void Unknown::BasicRenderComponent::render(const Entity &ent, double Xoffset, double Yoffset) const {
    auto& size = ent.prototype.size;

    UK_DRAW_RECT((ent.position.x - size.width / 2) * renderScale - Xoffset,
                 (ent.position.y - size.height / 2) * renderScale - Yoffset,
                 (size.width) * renderScale,
                 (size.height) * renderScale,
                 glm::degrees(ent.angle), this->col);
}

Unknown::BasicRenderComponent::BasicRenderComponent(Colour c) : BasicRenderComponent(c, 1) {}

void Unknown::BasicRenderComponent::update(Entity &ent) {}

Unknown::BasicRenderComponent::BasicRenderComponent(Colour c, int renderScale) : col(c), renderScale(renderScale) {
    editorColour.fill(0);
}

Unknown::BasicRenderComponent::BasicRenderComponent() : col(BLACK) {}

void Unknown::BasicRenderComponent::populateEditor() {
    editorColour[0] = col.red / 255.0;
    editorColour[1] = col.green / 255.0;
    editorColour[2] = col.blue / 255.0;
    editorColour[3] = col.alpha / 255.0;

    ImGui::BeginChild("Basic Renderer");
    ImGui::Text("Basic Renderer");
    ImGui::ColorEdit4("Colour", editorColour.data(), ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Float);
    ImGui::InputInt("Render scale", &this->renderScale);
    ImGui::EndChild();

    this->col = Colour(editorColour[0] * 255, editorColour[1] * 255, editorColour[2] * 255, editorColour[3] * 255);
}

Unknown::Rect<int> Unknown::BasicRenderComponent::getRenderBounds(const Entity &ent) {
    int Xoffset = 0, Yoffset = 0;
    auto& size = ent.prototype.size;

    return Rect<int>((ent.position.x - size.width / 2) * renderScale - Xoffset,
        (ent.position.y - size.height / 2) * renderScale - Yoffset,
        (size.width) * renderScale,
        (size.height) * renderScale);
}

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<BasicRenderComponent>("BasicRenderComponent")
            .property("Colour", &BasicRenderComponent::col)
            .property("RenderScale", &BasicRenderComponent::renderScale)
            .constructor<>();
};
