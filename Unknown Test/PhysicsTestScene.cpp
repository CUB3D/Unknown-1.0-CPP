//
// Created by cub3d on 28/07/2018.
//

#include <Loader.h>
#include <SharedVariable.h>
#include <Log.h>
#include "PhysicsTestScene.h"
#include "UI2D.h"
#include "KeyBind.h"
#include "Timer.h"
#include "Entity/Entity.h"
#include "Entity/PhysicsBodyComponent.h"
#include "PythonScript.h"
#include "Entity/TimerComponent.h"
#include "Font.h"

using namespace Unknown;
using namespace Unknown::Graphics;

KeyBind p1up(SDLK_UP, "jump");
KeyBind p1left(SDLK_LEFT, "left");
KeyBind p1right(SDLK_RIGHT, "right");
KeyBind p1fire(SDLK_RCTRL, "shoot");

KeyBind p2up(SDLK_w, "jump2");
KeyBind p2left(SDLK_a, "left2");
KeyBind p2right(SDLK_d, "right2");
KeyBind p2fire(SDLK_e, "shoot2");

bool p1onGround;
bool p2onGround;

int p1;
int p2;

SharedVariable p1Score("p1Score", std::string("0"));
SharedVariable p2Score("p2Score", std::string("0"));

UIContainer ui;

//TODO: particles;
//TODO: image renderer
//TODO: render map with camera
//TODO: render scene with camera
//TODO: ingame editor

//TODO: make sharedvar have a tostring method, store int conv to str for ui

PhysicsTestScene::PhysicsTestScene() : Scene("Phys") {
    UK_PYTHON_LOAD_SCRIPT("Test");
    ui = Loader::loadUI("PhysGameGUI.json");
    ui.setGlobalFont(std::make_shared<TTFont>("Fonts/Arimo-Regular.ttf", 15, UK_COLOUR_RGB(255, 255, 0)));
    ui.initUI();
    this->addObject(std::shared_ptr<UIContainer>(&ui, [](auto... dummy){}));

    this->addObject(UK_LOAD_ENTITY("Ground.json"));

    this->addObject(UK_LOAD_ENTITY_AT("OtherPlayerEntity.json", 5, 3));
    this->addObject(UK_LOAD_ENTITY_AT("PlayerEntity.json", 8, 3));

    this->addObject(UK_LOAD_ENTITY("Obstacle.json"));


    contactManager.addListener(getObject<Entity>("Player"), getObject<Entity>("Ground"), [](auto objs, bool onGround) {p1onGround = onGround;});
    contactManager.addListener(getObject<Entity>("Player"), getObject<Entity>("Obstacle"), [](auto bojs, bool onGround) {p1onGround = onGround;});
    contactManager.addListener(getObject<Entity>("OtherPlayer"), getObject<Entity>("Ground"), [](auto objs, bool onGround) {p2onGround = onGround;});
    contactManager.addListener(getObject<Entity>("OtherPlayer"), getObject<Entity>("Obstacle"), [](auto objs, bool onGround) {p2onGround = onGround;});
}


void PhysicsTestScene::update() {
    Scene::update();

    // Handle player 1 movement
    auto player = getObject<Entity>("Player");
    auto otherPlayer = getObject<Entity>("OtherPlayer");
    auto body = player->getComponent<PhysicsBodyComponent>()->body;

    if(p1up.pressed() && p1onGround) {
        body->ApplyForceToCenter(b2Vec2(0, -3000), true);
    }

    if(p1left.pressed()) {
        body->ApplyForceToCenter(b2Vec2(-200, 0), true);
    }

    if(p1right.pressed()) {
        body->ApplyForceToCenter(b2Vec2(200, 0), true);
    }

    if(p1fire.pressed()) {
        auto bullet = UK_LOAD_ENTITY_AT("Bullet.json", player->position.x + 1, player->position.y);
        bullet->getComponent<PhysicsBodyComponent>()->body->ApplyForceToCenter(b2Vec2(100, 0), true);
        this->addObject(bullet);
        contactManager.addListener(bullet, otherPlayer, [](auto objs, bool colliding) {
            if(colliding) {
                p1++;
                p1Score = intToString(p1);
                objs.first->queueDisable();
            }
        });
    }

    body = otherPlayer->getComponent<PhysicsBodyComponent>()->body;

    if(p2up.pressed() && p2onGround) {
        body->ApplyForceToCenter(b2Vec2(0, -1000), true);
    }

    if(p2left.pressed()) {
        body->ApplyForceToCenter(b2Vec2(-200, 0), true);
    }

    if(p2right.pressed()) {
        body->ApplyForceToCenter(b2Vec2(200, 0), true);
    }

    if(p2fire.pressed()) {
        auto bullet = UK_LOAD_ENTITY_AT("Bullet.json", otherPlayer->position.x + 1, otherPlayer->position.y);
        bullet->getComponent<PhysicsBodyComponent>()->body->ApplyForceToCenter(b2Vec2(100, 0), true);
        this->addObject(bullet);
        contactManager.addListener(bullet, player, [](auto objs, bool colliding) {
            if(colliding) {
                p2++;
                p2Score = intToString(p2);
                objs.first->queueDisable();
            }
        });
    }

    auto bullets = getObjects<Entity>("Bullet");

    for(auto& bullet : bullets) {
        if(bullet->enabled) {
            auto timer = bullet->getComponent<TimerComponent>();
            if (timer->t.isTickComplete()) {
                bullet->disable();
            }
        }
    }
}
