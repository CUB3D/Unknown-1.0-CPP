//
// Created by cub3d on 12/08/18.
//

#include "AnimationRenderComponent.h"

Unknown::AnimationRenderComponent::AnimationRenderComponent(::Unknown::Graphics::Animation animation1) : animation(animation1) {}

void Unknown::AnimationRenderComponent::render(const ::Unknown::Entity &ent, double xoff, double yoff) const {
    animation.drawNoAdvance(ent.position.x, ent.position.y, ent.angle);
}

void Unknown::AnimationRenderComponent::update(::Unknown::Entity &ent) {
    animation.attemptAdvanceFrame();
}
