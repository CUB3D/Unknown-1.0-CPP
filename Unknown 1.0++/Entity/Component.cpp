//
// Created by cub3d on 29/07/2018.
//

#include "Component.h"
#include "Entity.h"

void Unknown::Component::update(::Unknown::Entity &ent) {}

void Unknown::Component::render(const Entity &ent, double Xoffset, double Yoffset) const {}

void Unknown::Component::onDisable(::Unknown::Entity &ent) {}

void Unknown::Component::populateEditor() {}

const std::string Unknown::Component::getName() {
    return "Component";
}
