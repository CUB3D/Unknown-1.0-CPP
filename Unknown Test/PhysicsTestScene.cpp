//
// Created by cub3d on 28/07/2018.
//

#include <Loader.h>
#include <SharedVariable.h>
#include <Log.h>
#include <Font/TTFont.h>
#include "PhysicsTestScene.h"
#include "UI2D.h"
#include "KeyBind.h"
#include "Timer.h"
#include "Entity/Entity.h"
#include "Entity/PhysicsBodyComponent.h"
#include "PythonScript.h"
#include "Entity/TimerComponent.h"
#include "Font/Font.h"
#include "Audio/WAVSound.h"
#include "Editor/EditorBase.h"

using namespace ::Unknown;
using namespace ::Unknown::Graphics;

KeyBind p1up(SDLK_UP, "jump");
KeyBind p1left(SDLK_LEFT, "left");
KeyBind p1right(SDLK_RIGHT, "right");
KeyBind p1fire(SDLK_RCTRL, "shoot");
Timer p1FireTimer(0.3f);

KeyBind p2up(SDLK_w, "jump2");
KeyBind p2left(SDLK_a, "left2");
KeyBind p2right(SDLK_d, "right2");
KeyBind p2fire(SDLK_e, "shoot2");
Timer p2FireTimer(0.3f);

bool p1onGround;
bool p2onGround;

SharedVariable p1Score("p1Score", 0.0);
SharedVariable p2Score("p2Score", 0.0);

UIContainer ui;

WAVSound fire("Fire.wav");
WAVSound hit("Hit.wav");

//TODO: particles;
//TODO: image renderer
//TODO: render map with camera
//TODO: render scene with camera
//TODO: ingame editor



PhysicsTestScene::PhysicsTestScene() : Scene("Phys") {
    //UK_PYTHON_LOAD_SCRIPT("Test");
    ui = Loader::loadUI("PhysGameGUI.json");
    ui.setGlobalFont(std::make_shared<::Unknown::Graphics::TTFont>("Fonts/Arimo-Regular.ttf", 15, UK_COLOUR_RGB(255, 255, 0)));
    ui.initUI();

    this->addObject(std::shared_ptr<UIContainer>(&ui, [](auto... dummy){}));

    this->addObject(UK_LOAD_ENTITY("Ground.json"));

    this->addObject(UK_LOAD_ENTITY_AT("OtherPlayerEntity.json", 5, 3));
    this->addObject(UK_LOAD_ENTITY_AT("PlayerEntity.json", 16, 3));

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
    auto body = player->getComponent<PhysicsBodyComponent>();
    body->body->SetSleepingAllowed(false);

    if(p1up.pressed() && p1onGround) {
       body->applyForce(Vector(0, -3000));
    }

    //TODO: finish rendering offsets

    if(p1left.pressed()) {
        //body->applyForce(Vector(-200, 0));
        cam.area.x--;
        auto t = body->body->GetPosition();
        t.x -= 1/32.0;
        body->body->SetTransform(t, body->body->GetAngle());
    }

    if(p1right.pressed()) {
        //body->applyForce(Vector(200, 0));
        cam.area.x++;
        auto t = body->body->GetPosition();
        t.x += 1/32.0;
        body->body->SetTransform(t, body->body->GetAngle());
    }

    if(p1fire.pressed() && p1FireTimer.isTickComplete()) {
        fire.playSingle();

        auto bullet = UK_LOAD_ENTITY_AT("Bullet.json", player->position.x + 1, player->position.y);

        auto vec = player->getComponent<PhysicsBodyComponent>()->getXDirection() * 100;

        bullet->getComponent<PhysicsBodyComponent>()->body->ApplyForceToCenter(vec, true);
        this->addObject(bullet);
        contactManager.addListener(bullet, otherPlayer, [](auto objs, bool colliding) {
            if(colliding) {
                hit.playSingle();
                p1Score++;
                objs.first->queueDisable();
            }
        });
    }

    body = otherPlayer->getComponent<PhysicsBodyComponent>();

    if(p2up.pressed() && p2onGround) {
        body->applyForce(Vector(0, -3000));
    }

    if(p2left.pressed()) {
        body->applyForce(Vector(-200, 0));
    }

    if(p2right.pressed()) {
        body->applyForce(Vector(200, 0));
    }

    if(p2fire.pressed() && p2FireTimer.isTickComplete()) {
        fire.playSingle();

        auto bullet = UK_LOAD_ENTITY_AT("OtherBullet.json", otherPlayer->position.x + 1, otherPlayer->position.y);

        auto vec = otherPlayer->getComponent<PhysicsBodyComponent>()->getXDirection() * 100;

        bullet->getComponent<PhysicsBodyComponent>()->body->ApplyForceToCenter(vec, true);
        this->addObject(bullet);
        contactManager.addListener(bullet, player, [](auto objs, bool colliding) {
            if(colliding) {
                hit.playSingle();
                p2Score++;
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

void PhysicsTestScene::render() const {
    UK_DRAW_RECT(0, 0, 1024, 1024, UK_COLOUR_RGB(0, 0, 0));
    Scene::render();
}
