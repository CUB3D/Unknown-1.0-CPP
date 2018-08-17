//
// Created by cub3d on 29/07/2018.
//

#include "BasicRenderComponent.h"
#include "../UI2D.h"
#include "../Editor/imgui.h"


void Unknown::BasicRenderComponent::render(const Entity &ent, double Xoffset, double Yoffset) const {
    UK_DRAW_RECT((ent.position.x - ent.size.width / 2) * renderScale - Xoffset,
                 (ent.position.y - ent.size.height / 2) * renderScale - Yoffset,
                 (ent.size.width) * renderScale,
                 (ent.size.height) * renderScale,
                 ent.angle, this->col);

    ::Unknown::Graphics::drawCircle(300, 300, 100, UK_COLOUR_RGB(255, 255, 0));
}

Unknown::BasicRenderComponent::BasicRenderComponent(Colour c) : BasicRenderComponent(c, 1) {}

void Unknown::BasicRenderComponent::update(Entity &ent) {}

Unknown::BasicRenderComponent::BasicRenderComponent(Colour c, int renderScale) : col(c), renderScale(renderScale) {
    editorColour.fill(0);
}

Unknown::BasicRenderComponent::BasicRenderComponent() : col(Colour::BLACK) {}

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

    //R G B A
    //A R G B

    this->col = Colour(editorColour[0] * 255, editorColour[1] * 255, editorColour[2] * 255, editorColour[3] * 255);
}
