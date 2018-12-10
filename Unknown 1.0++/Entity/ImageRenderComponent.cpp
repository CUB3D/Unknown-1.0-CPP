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

    img.render((ent.position.x - size.width / 2) * renderScale - Xoffset,
               (ent.position.y - size.height / 2) * renderScale - Yoffset, glm::degrees(ent.angle));
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

    return ::Unknown::Rect<int>((ent.position.x - size.width / 2) * renderScale - Xoffset,
                              (ent.position.y - size.height / 2) * renderScale - Yoffset, img.imageSize.width, img.imageSize.height);
}

void Unknown::ImageRenderComponent::update(Unknown::Entity &ent) {
    auto& size = ent.prototype.size;

    img.renderScale = Dimension<float>(
        (float) (renderScale * size.width) / (float) img.imageSize.width,
        (float) (renderScale * size.height) / (float) img.imageSize.height);
}

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<ImageRenderComponent>("ImageRenderComponent")
            .property("Image", &ImageRenderComponent::img)
            .property("RenderScale", &ImageRenderComponent::renderScale)
            .constructor<>();
};
