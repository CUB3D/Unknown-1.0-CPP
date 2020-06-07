//
// Created by cub3d on 02/08/18.
//

#include "ImageRenderComponent.h"
#include <Types/Rect.h>
#include <Imgui/GUI.h>
#include <Entity/Entity.h>

Unknown::ImageRenderComponent::ImageRenderComponent(const std::string &filename, const int renderScale) : img(filename), renderScale(renderScale) {}

Unknown::ImageRenderComponent::ImageRenderComponent() : ImageRenderComponent("", 1) {}

void Unknown::ImageRenderComponent::render(const Entity &ent, double Xoffset, double Yoffset) const {

    auto& size = ent.prototype.size;

    img.render((ent.position.x - size.x / 2) * renderScale - Xoffset,
               (ent.position.y - size.y / 2) * renderScale - Yoffset, glm::degrees(ent.angle));
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
    auto& size = ent.prototype.size;

    return ::Unknown::Rect<int>((ent.position.x - size.x / 2) * renderScale - Xoffset,
                              (ent.position.y - size.y / 2) * renderScale - Yoffset, img.imageSize.x, img.imageSize.y);
}

void Unknown::ImageRenderComponent::update(Unknown::Entity &ent) {
    auto& size = ent.prototype.size;

    img.renderScale = glm::vec2(
        (float) (renderScale * size.x) / (float) img.imageSize.x,
        (float) (renderScale * size.y) / (float) img.imageSize.y);
}

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<ImageRenderComponent>("ImageRenderComponent")
            .property("Image", &ImageRenderComponent::img)
            .property("RenderScale", &ImageRenderComponent::renderScale)
            .constructor<>();
};
