//
// Created by cub3d on 28/07/2018.
//

#include <Loader.h>
#include "PhysicsTestScene.h"
#include "UI2D.h"
#include "KeyBind.h"
#include "Timer.h"
#include "ContactListener.h"
#include "Entity/Entity.h"
#include "Entity/PhysicsBodyComponent.h"
#include "PythonScript.h"

#define PIX_TO_METER 32

Unknown::KeyBind up(SDLK_UP, "jump");
Unknown::KeyBind left(SDLK_LEFT, "left");
Unknown::KeyBind right(SDLK_RIGHT, "right");
Unknown::Timer jumpdelay(0.1f);
ContactListener ctlist;

//TODO: get component by id/tag/name
std::shared_ptr<Unknown::Entity> player;
std::shared_ptr<Unknown::PhysicsBodyComponent> phys;


//TODO: particles
//TODO: image renderer


PhysicsTestScene::PhysicsTestScene() : Scene("Phys") {

    this->world.SetContactListener(&ctlist);

    this->addObject(Unknown::Loader::loadEntityAt("Ground.json", *this, 15, 25));

    for(int x = 0; x < 3; x ++) {
        this->addObject(Unknown::Loader::loadEntityAt("Obstacle.json", *this, 5 * x, 14));
    }

    this->addObject(Unknown::Loader::loadEntityAt("PlayerEntity.json", *this, 5, 3));


    player = Unknown::Loader::loadEntityAt("PlayerEntity.json", *this, 6, 3);
    phys = player->getComponent<Unknown::PhysicsBodyComponent>();
    this->addObject(player);

    UK_PYTHON_LOAD_SCRIPT("Test");
    Unknown::Python::getInterpreter()->callMethod("Test.hello", nullptr); //functions that create wrappers around python methods
}

void PhysicsTestScene::update() {
    Scene::update();

    if(up.pressed() && jumpdelay.isTickComplete() && ctlist.onground) {
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
