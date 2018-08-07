//
// Created by cub3d on 02/08/18.
//

#include "ImageRenderComponent.h"

Unknown::ImageRenderComponent::ImageRenderComponent(const std::string &filename, const int renderScale) : img(filename), renderScale(renderScale) {}

void Unknown::ImageRenderComponent::render(const Entity &ent, double Xoffset, double Yoffset) const {
    img.render((ent.position.x - ent.size.width / 2) * renderScale - Xoffset,
               (ent.position.y - ent.size.height / 2) * renderScale - Yoffset, (ent.angle / 3.141) * 180);
}
