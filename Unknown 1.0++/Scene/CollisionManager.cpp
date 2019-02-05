//
// Created by cub3d on 31/07/18.
//

#include <functional>
#include "CollisionManager.h"
#include "../Entity/PhysicsBodyComponent.h"
#include "../Log.h"

void Unknown::CollisionManager::addListener(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b,
                                            std::function<void(std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> objs, bool inContact)> callback) {

    if(!a || !b) {
        UK_LOG_ERROR("Attempted to register collision listener between null entities");
        return;
    }

    auto physA = a->getComponent<PhysicsBodyComponent>();
    auto physB = b->getComponent<PhysicsBodyComponent>();

    if(!(physA && physB)) {
        UK_LOG_ERROR("Denied, attempt to register a collision listener between non physics components");
        return;
    }


    listeners[std::pair(a, b)] = callback;
}

void Unknown::CollisionManager::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);

    for(auto& key : this->listeners) {
        auto fixB = key.first.first->getComponent<PhysicsBodyComponent>()->body;
        auto fixA = key.first.second->getComponent<PhysicsBodyComponent>()->body;
        if(contact->GetFixtureA()->GetBody() == fixA && contact->GetFixtureB()->GetBody() == fixB) {
            key.second(key.first, true);
        } else {
            if (contact->GetFixtureA()->GetBody() == fixB && contact->GetFixtureB()->GetBody() == fixA) {
                key.second(key.first, true);
            }
        }
    }
}

void Unknown::CollisionManager::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);

    for(auto& key : this->listeners) {
        auto fixB = key.first.first->getComponent<PhysicsBodyComponent>()->body;
        auto fixA = key.first.second->getComponent<PhysicsBodyComponent>()->body;
        if(contact->GetFixtureA()->GetBody() == fixA && contact->GetFixtureB()->GetBody() == fixB) {
            key.second(key.first, false);
        } else {
            if (contact->GetFixtureA()->GetBody() == fixB && contact->GetFixtureB()->GetBody() == fixA) {
                key.second(key.first, false);
            }
        }
    }
}

void Unknown::CollisionManager::reset() {
    this->listeners.clear();
}
