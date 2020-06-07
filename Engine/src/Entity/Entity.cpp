//
// Created by cub3d on 29/07/2018.
//

#include "Entity.h"
#include "PhysicsBodyComponent.h"
#include "ImageRenderComponent.h"
#include "BasicRenderComponent.h"

Unknown::Entity::Entity(EntityPrototype proto) : position(0, 0), enabled(true), queueDissable(false), angle(0), prototype(proto) {}

void Unknown::Entity::render(double Xoffset, double Yoffset) const {
    if(!enabled)
        return;
    for(auto& component : getComponents()) {
        component->render(*this, Xoffset, Yoffset);
    }
}

void Unknown::Entity::update() {
    if(!enabled)
        return;

    if(queueDissable) {
        this->disable();
        queueDissable = false;
    }
    for(auto& component : getComponents()) {
        component->update(*this);
    }
}


Unknown::Rect<int> Unknown::Entity::getRenderBounds() {
    auto&& i = getComponent<ImageRenderComponent>();
    if(i) {
        return i->getRenderBounds(*this);
    }

    auto&& ii = getComponent<BasicRenderComponent>();
    if(ii) {
        return ii->getRenderBounds(*this);
    }

    return Rect<int>(position.x, position.y, prototype.size.x, prototype.size.y);
}

void Unknown::Entity::setPosition(double x, double y, double angle) {
    this->position = glm::vec2(x, y);
    this->angle = angle;

    auto physicsComp = getComponent<PhysicsBodyComponent>();
    if(physicsComp) {
        // Check to see if it has been inited
        if(!physicsComp->body) {
            return;
        }

        physicsComp->body->SetTransform(b2Vec2(x, y), angle);
        // Make sure to wake the body so that phys sim keeps working
        physicsComp->body->SetAwake(true);
    }
}

const std::string Unknown::Entity::getTag() const {
    return this->prototype.tag;
}

void Unknown::Entity::disable() {
    this->enabled = false;

    for(auto& component : getComponents()) {
        component->onDisable(*this);
    }
}

void Unknown::Entity::queueDisable() {
    this->queueDissable = true;
}

void Unknown::Entity::move(double x, double y) {
    setPosition(position.x + x, position.y + y);
}

void Unknown::Entity::rotate(double delta) {
    setPosition(position.x, position.y, angle + delta);
}

std::vector<std::shared_ptr<Unknown::Component>> Unknown::Entity::getComponents() const {
    return this->prototype.components;
}
