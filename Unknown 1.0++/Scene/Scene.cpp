//
// Created by cub3d on 01/06/17.
//
#include "../stdafx.h"
#include "Scene.h"
#include "../Loader.h"
#include "../Font.h"

Unknown::Scene::Scene(const std::string name) : name(name), world(b2Vec2(0, 9.8f))
{
}

void Unknown::Scene::update()
{
   this->world.Step(1/60.0f, 8, 8);
}

void Unknown::Scene::render() const {
    for(auto& renderable : this->renderables) {
        renderable->render();
    }
}

Unknown::MenuScene::MenuScene(const std::string name, std::string uiFile, std::shared_ptr<Graphics::Font> font) : Scene(name), uiFile(uiFile), font(font)
{
    if(!uiFile.empty()) {
        this->menu = Loader::loadUI(uiFile);
    } else {
        this->menu = UIContainer();
    }
    this->menu.setGlobalFont(font);
    this->menu.initUI();
}

void Unknown::MenuScene::render() const
{
    this->menu.renderUI();
    Scene::render();
}

void Unknown::MenuScene::update()
{
    Scene::update();
}

void Unknown::MenuScene::reloadMenu() {
    // TODO: quick and dirty for getting resizing ui's, make a way to recalculate offsets inplace
    this->menu = Loader::loadUI(this->uiFile);
    this->menu.setGlobalFont(this->font);
    this->menu.initUI();
}

Unknown::CustomScene::CustomScene(const std::string name, std::function<void(void)> renderer, std::function<void(void)> updater) : Scene(name), renderer(renderer), updater(updater)
{
}

void Unknown::CustomScene::render() const
{
    if(this->renderer)
        this->renderer();
    Scene::render();
}

void Unknown::CustomScene::update()
{
    if(this->updater)
        this->updater();
    Scene::update();
}
