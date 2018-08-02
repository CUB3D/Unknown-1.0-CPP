//
// Created by cub3d on 29/07/2018.
//

#include "Entity.h"
#include "PhysicsBodyComponent.h"

void Unknown::Entity::render() const {
    if(!enabled)
        return;
    for(auto& component : this->components) {
        component->render(*this);
    }
}

void Unknown::Entity::update() {
    if(!enabled)
        return;

    if(queueDissable) {
        this->disable();
        queueDissable = false;
    }
    for(auto& component : this->components) {
        component->update(*this);
    }
}


Unknown::Rect<int> Unknown::Entity::getRenderBounds() {
    return Rect<int>(position.x, position.y, size.height, size.width);
}

Unknown::Entity::Entity(const std::string& tag) : size(0, 0), position(0, 0), tag(tag), enabled(true), queueDissable(false) {}

void Unknown::Entity::setPosition(double x, double y) {
    this->position = Point<double>(x, y);
    auto physicsComp = getComponent<PhysicsBodyComponent>();
    if(physicsComp) {
        physicsComp->body->SetTransform(b2Vec2(x, y), physicsComp->body->GetAngle());
    }
}

const std::string Unknown::Entity::getTag() const {
    return this->tag;
}

void Unknown::Entity::disable() {
    this->enabled = false;

    for(auto& component : this->components) {
        component->onDisable(*this);
    }
}

void Unknown::Entity::queueDisable() {
    this->queueDissable = true;
}
