//
// Created by cub3d on 28/07/2018.
//

#include "PhysicsTestScene.h"
#include "UI2D.h"
#include "KeyBind.h"
#include "Timer.h"
#include "ContactListener.h"
#include "Entity/Entity.h"
#include "Entity/BasicRenderComponent.h"
#include "Entity/PhysicsBodyComponent.h"


#define PIX_TO_METER 32

Unknown::KeyBind up(SDLK_UP, "jump");
Unknown::KeyBind left(SDLK_LEFT, "left");
Unknown::KeyBind right(SDLK_RIGHT, "right");
Unknown::Timer jumpdelay(0.1f);
ContactListener ctlist;

std::shared_ptr<Unknown::Entity> testEnt;
//TODO: get component by id/tag/name
std::shared_ptr<Unknown::Entity> player;
std::shared_ptr<Unknown::PhysicsBodyComponent> phys;
std::shared_ptr<Unknown::Entity> ground;
std::vector<std::shared_ptr<Unknown::Entity>> obstacles1;



PhysicsTestScene::PhysicsTestScene() : Scene("Phys") {

    this->world.SetContactListener(&ctlist);

//    groundBody.position.Set(15.0f, 25.0f);
//    groundBodyObj = this->world.CreateBody(&groundBody);
//    groundShape.SetAsBox(10.0f, 10.0f);
//    groundBodyObj->CreateFixture(&groundShape, 0);

    ground = std::make_shared<Unknown::Entity>();
    ground->position = Unknown::Point<double>(15, 25.0);
    ground->size = Unknown::Dimension<int>(20, 20);
    ground->components.push_back(std::make_shared<Unknown::BasicRenderComponent>(Unknown::Colour::GREEN, PIX_TO_METER));
    ground->components.push_back(std::make_shared<Unknown::PhysicsBodyComponent>(ground, this, b2_staticBody));
    this->renderables.push_back(ground);
    this->updatables.push_back(ground);

    for(int x = 0; x < 3; x ++) {
        auto obstacle = std::make_shared<Unknown::Entity>();
        obstacle->position = Unknown::Point<double>(5 * x, 14);
        obstacle->size = Unknown::Dimension<int>(2, 2);
        obstacle->components.push_back(std::make_shared<Unknown::BasicRenderComponent>(Unknown::Colour::BLUE, PIX_TO_METER));
        obstacle->components.push_back(std::make_shared<Unknown::PhysicsBodyComponent>(obstacle, this, b2_staticBody));
        this->renderables.push_back(obstacle);
        obstacles1.push_back(obstacle);
    }

    testEnt = std::make_shared<Unknown::Entity>();
    testEnt->position = Unknown::Point<double>(5, 3.0);
    testEnt->size = Unknown::Dimension<int>(2, 2);
    testEnt->components.push_back(std::make_shared<Unknown::BasicRenderComponent>(Unknown::Colour::BLUE, PIX_TO_METER));
    testEnt->components.push_back(std::make_shared<Unknown::PhysicsBodyComponent>(testEnt, this, b2_dynamicBody));
    this->renderables.push_back(testEnt);
    this->updatables.push_back(testEnt);

    player = std::make_shared<Unknown::Entity>();
    player->position = Unknown::Point<double>(6, 3);
    player->size = Unknown::Dimension<int>(2, 2);
    player->components.push_back(std::make_shared<Unknown::BasicRenderComponent>(Unknown::Colour::RED, PIX_TO_METER));
    phys = std::make_shared<Unknown::PhysicsBodyComponent>(player, this, b2_dynamicBody);
    player->components.push_back(phys);
    this->renderables.push_back(player);
    this->updatables.push_back(player);
}

void PhysicsTestScene::update() {
    Scene::update();

    if(up.pressed() && jumpdelay.isTickComplete() && ctlist.onground) {
        printf("Test");
        phys->body->ApplyForceToCenter(b2Vec2(0, -3000), true);
    }

    if(phys->body->GetLinearVelocity().Length() > 10) {
        //TODO: better way of setting max speed
        auto noramlised = phys->body->GetLinearVelocity();
        noramlised.Normalize();
        noramlised *= 10;
        phys->body->SetLinearVelocity(noramlised);
    }

    if(left.pressed()) {
        phys->body->ApplyForceToCenter(b2Vec2(-200, 0), true);
    }

    if(right.pressed()) {
        phys->body->ApplyForceToCenter(b2Vec2(200, 0), true);
    }
}
