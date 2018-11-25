//
// Created by cub3d on 29/07/2018.
//

#include "PhysicsBodyComponent.h"

//TODO: better way of doing this, also dont take pointer

Unknown::PhysicsBodyComponent::PhysicsBodyComponent(std::shared_ptr<Entity> ent) : body(nullptr), fixture(nullptr) {
    this->bodyDefinition.position.Set(ent->position.x, ent->position.y);
}

Unknown::PhysicsBodyComponent::PhysicsBodyComponent() : body(nullptr), fixture(nullptr) {
    this->bodyDefinition.position.Set(0, 0);
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

void Unknown::PhysicsBodyComponent::init(Scene &scene, std::shared_ptr<Entity> ent) {
    this->body = scene.world.CreateBody(&this->bodyDefinition);

    this->shape.SetAsBox(ent->size.width / 2.0, ent->size.height / 2.0);
    this->circle.m_p.Set(0, 0);
    body->SetTransform(b2Vec2(ent->position.x, ent->position.y), ent->angle);
    body->SetAwake(true);

//    this->fixtureDefinition.friction = 0.9f; //TODO:
    this->fixtureDefinition.filter = filter;
//    this->fixtureDefinition.restitution = 0.3; //TODO:

    this->fixture = this->body->CreateFixture(&this->fixtureDefinition);

}


RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<PhysicsBodyComponent>("PhysicsBodyComponent")
            .property("bodyDefinition", &PhysicsBodyComponent::bodyDefinition)
            .constructor<>();

    // Add bod2d classes
    rttr::registration::class_<b2BodyDef>("BodyDefinition")
            //TODO
            .property("angle", &b2BodyDef::angle)
            .constructor<>();
};