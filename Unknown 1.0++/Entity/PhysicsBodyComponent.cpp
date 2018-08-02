//
// Created by cub3d on 29/07/2018.
//

#include "PhysicsBodyComponent.h"

//TODO: better way of doing this

Unknown::PhysicsBodyComponent::PhysicsBodyComponent(std::shared_ptr<Entity> ent, Scene *scene, b2BodyType type,
                                                    const bool bullet, int groupIndex) {
    this->bodyDefinition.type = type;
   // this->bodyDefinition.fixedRotation = true; //TODO:
    this->bodyDefinition.position.Set(ent->position.x, ent->position.y);
    this->bodyDefinition.bullet = bullet;

    this->filter.groupIndex = groupIndex;

    this->body = scene->world.CreateBody(&this->bodyDefinition);

    this->shape.SetAsBox(ent->size.width / 2.0, ent->size.height / 2.0);

    this->fixtureDefinition.shape = &this->shape;
    this->fixtureDefinition.density = 1.0f; //TODO:
    this->fixtureDefinition.friction = 0.9f; //TODO:
    this->fixtureDefinition.filter = filter;

    this->fixture = this->body->CreateFixture(&this->fixtureDefinition);
}

void Unknown::PhysicsBodyComponent::update(Entity &ent) {

    if(maxSpeed >= 0) {
        // If the current speed is > maxspeed
        if (body->GetLinearVelocity().Length() > maxSpeed) {
            auto noramlised = body->GetLinearVelocity();
            // Get direction
            noramlised.Normalize();
            // Get vector of max speed in cur direction
            noramlised *= maxSpeed;
            body->SetLinearVelocity(noramlised);
        }
    }

    ent.position.x = body->GetPosition().x;
    ent.position.y = body->GetPosition().y;
    ent.angle = body->GetAngle();
}

void Unknown::PhysicsBodyComponent::onDisable(Entity &ent) {
    this->body->GetWorld()->DestroyBody(this->body);
}

Unknown::Vector Unknown::PhysicsBodyComponent::getXDirection() const {
    b2Vec2 vec = lastForce;
    vec.y = 0;
    vec.Normalize();
    return Vector(vec);
}

void Unknown::PhysicsBodyComponent::applyForce(const Vector &vec) {
    this->body->ApplyForceToCenter(vec.getBox2DVec(), true);
    this->lastForce = vec;
}
