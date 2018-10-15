//
// Created by cub3d on 02/08/18.
//

#include "ImageRenderComponent.h"
#include "../Utils.h"
#include "../Editor/imgui.h"

Unknown::ImageRenderComponent::ImageRenderComponent(const std::string &filename, const int renderScale) : img(filename), renderScale(renderScale) {}

void Unknown::ImageRenderComponent::render(const Entity &ent, double Xoffset, double Yoffset) const {
    img.render((ent.position.x - ent.size.width / 2) * renderScale - Xoffset,
               (ent.position.y - ent.size.height / 2) * renderScale - Yoffset, glm::degrees(ent.angle));
}

void Unknown::ImageRenderComponent::populateEditor() {
    // Some kind of resource id system,
    // can show a drop down to select the resource id you want to use from all of the ones that are loaded
    // somehow map resource id to image, maybe some kind of abstract class

    ImGui::BeginChild("Image Renderer");
    ImGui::Text("Image Renderer");
    ImGui::InputInt("Render scale", &this->renderScale);
    ImGui::EndChild();
}

Unknown::Rect<int> Unknown::ImageRenderComponent::getRenderBounds(const Entity &ent) {
    int Xoffset = 0;
    int Yoffset = 0;

    return ::Unknown::Rect<int>((ent.position.x - ent.size.width / 2) * renderScale - Xoffset,
                              (ent.position.y - ent.size.height / 2) * renderScale - Yoffset, img.imageSize.width, img.imageSize.height);
}
