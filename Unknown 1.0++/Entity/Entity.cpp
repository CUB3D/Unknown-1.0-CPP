//
// Created by cub3d on 29/07/2018.
//

#include "Entity.h"
#include "PhysicsBodyComponent.h"

void Unknown::Entity::render() const {
    for(auto& component : this->components) {
        component->render(*this);
    }
}

void Unknown::Entity::update() {
    for(auto& component : this->components) {
        component->update(*this);
    }
}

Unknown::Entity *Unknown::Entity::clone() {
    return nullptr;
}

Unknown::Rect<int> Unknown::Entity::getRenderBounds() {
    return Rect<int>(position.x, position.y, size.height, size.width);
}

Unknown::Entity::Entity() : size(0, 0), position(0, 0) {}

void Unknown::Entity::setPosition(double x, double y) {
    this->position = Point<double>(x, y);
    auto physicsComp = getComponent<PhysicsBodyComponent>();
    if(physicsComp) {
        physicsComp->body->SetTransform(b2Vec2(x, y), physicsComp->body->GetAngle());
    }
}
