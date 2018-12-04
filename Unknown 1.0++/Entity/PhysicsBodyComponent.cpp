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

    if(maxSpeed.x > 0 || maxSpeed.y > 0) {
        auto lin = body->GetLinearVelocity();

        // If the current speed is > maxspeed
        if (std::abs(lin.x) > maxSpeed.x) {
            auto normalised = lin;
            // Get direction
            normalised.Normalize();
            body->SetLinearVelocity(b2Vec2(normalised.x * maxSpeed.x, lin.y));
        }


        if (std::abs(lin.y) > maxSpeed.y) {
            auto normalised = lin;
            // Get direction
            normalised.Normalize();
            body->SetLinearVelocity(b2Vec2(lin.x, normalised.y * maxSpeed.y));
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
    auto& size = ent->prototype.size;

    this->body = scene.world.CreateBody(&this->bodyDefinition);
    printf("Created rest: %lf\n", this->fixtureDefinition.restitution);

    this->shape.SetAsBox(size.width / 2.0, size.height / 2.0);
    this->circle.m_p.Set(0, 0);
    body->SetTransform(b2Vec2(ent->position.x, ent->position.y), ent->angle);
    body->SetAwake(true);

    fixtureDefinition.shape = &shape;//TODO:

    this->fixture = this->body->CreateFixture(&this->fixtureDefinition);

}


RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<PhysicsBodyComponent>("PhysicsBodyComponent")
            .property("BodyDefinition", &PhysicsBodyComponent::bodyDefinition)
            .property("MaxSpeed", &PhysicsBodyComponent::maxSpeed)
            .property("FixtureDefinition", &PhysicsBodyComponent::fixtureDefinition)
            .constructor<>();

    // Add bod2d classes

    //b2BodyDef
    rttr::registration::class_<b2BodyDef>("BodyDefinition")
        .property("Type", &b2BodyDef::type)
        .property("Position", &b2BodyDef::position)
        .property("Angle", &b2BodyDef::angle)
        .property("LinearVelocity", &b2BodyDef::linearVelocity)
        .property("LinearDamping", &b2BodyDef::linearDamping)
        .property("AllowSleep", &b2BodyDef::allowSleep)
        .property("Awake", &b2BodyDef::awake)
        .property("FixedRotation", &b2BodyDef::fixedRotation)
        .property("Bullet", &b2BodyDef::bullet)
        .property("Active", &b2BodyDef::active)
        .property("GravityScale", &b2BodyDef::gravityScale)
        .constructor<>();

    //b2Vec2
    rttr::registration::class_<b2Vec2>("Vec2")
        .property("X", &b2Vec2::x)
        .property("Y", &b2Vec2::y)
        .constructor<>();

    //b2BodyType
    rttr::registration::enumeration<b2BodyType>("BodyType")
        (
            rttr::value("StaticBody", b2BodyType::b2_staticBody),
            rttr::value("KinematicBody", b2BodyType::b2_kinematicBody),
            rttr::value("DynamicBody", b2BodyType::b2_dynamicBody)
        );

    //b2FixtureDef
    rttr::registration::class_<b2FixtureDef>("FixtureDefinition")
        .property("Friction", &b2FixtureDef::friction)
        .property("Restitution", &b2FixtureDef::restitution)
        .property("Density", &b2FixtureDef::density)
        .property("isSensor", &b2FixtureDef::isSensor)
        .property("Filter", &b2FixtureDef::filter)
        .constructor<>();

    //b2FixtureDef
    rttr::registration::class_<b2Filter>("Filter")
        .property("Category", &b2Filter::categoryBits)
        .property("Mask", &b2Filter::maskBits)
        .property("Group", &b2Filter::groupIndex)
        .constructor<>();
};