//
// Created by cub3d on 29/07/2018.
//

#include "BasicRenderComponent.h"
#include "../UI2D.h"


void Unknown::BasicRenderComponent::render(const Entity& ent) const {
    UK_DRAW_RECT((ent.position.x - ent.size.width / 2) * renderScale,
                 (ent.position.y - ent.size.height / 2) * renderScale,
                 (ent.size.width) * renderScale,
                 (ent.size.height) * renderScale, this->col);
}

Unknown::BasicRenderComponent::BasicRenderComponent(Colour c) : BasicRenderComponent(c, 1) {}

void Unknown::BasicRenderComponent::update(Entity &ent) {}

Unknown::BasicRenderComponent::BasicRenderComponent(Colour c, int renderScale) : col(c), renderScale(renderScale) {

}
