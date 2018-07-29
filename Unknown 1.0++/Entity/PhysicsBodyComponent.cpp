//
// Created by cub3d on 29/07/2018.
//

#include "PhysicsBodyComponent.h"

//TODO: better way of doing this

Unknown::PhysicsBodyComponent::PhysicsBodyComponent(std::shared_ptr<Entity> ent, Scene *scene, b2BodyType type) {
    this->bodyDefinition.type = type;
    this->bodyDefinition.fixedRotation = true;
    this->bodyDefinition.position.Set(ent->position.x, ent->position.y);

    this->body = scene->world.CreateBody(&this->bodyDefinition);
    this->shape.SetAsBox(ent->size.width / 2.0, ent->size.height / 2.0);
    this->fixtureDefinition.shape = &this->shape;
    this->fixtureDefinition.density = 1.0f;
    this->fixtureDefinition.friction = 0.9f;
    this->body->CreateFixture(&this->fixtureDefinition);
}

void Unknown::PhysicsBodyComponent::update(Entity &ent) {
    printf("%d\n", ent.position.y);
    ent.position.x = body->GetPosition().x;
    ent.position.y = body->GetPosition().y;
}
