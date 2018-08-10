//
// Created by cub3d on 29/07/2018.
//

#include "BasicRenderComponent.h"
#include "../UI2D.h"


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

}

Unknown::BasicRenderComponent::BasicRenderComponent() : col(Colour::BLACK) {}
