//
// Created by cub3d on 01/06/17.
//
#include "stdafx.h"
#include "Scene.h"
#include "../Loader.h"
#include "../Font.h"

Unknown::Scene::Scene(const std::string name) : name(name)
{
}

Unknown::MenuScene::MenuScene(const std::string name, std::string uiFile, Graphics::Font* font) : Scene(name)
{
    this->menu = Loader::loadUI(uiFile.c_str());
    this->menu.setGlobalFont(font);
    this->menu.initUI();
}

void Unknown::MenuScene::render() const
{
    this->menu.renderUI();
}

void Unknown::MenuScene::update()
{

}

Unknown::CustomScene::CustomScene(const std::string name, std::function<void(void)> renderer, std::function<void(void)> updater) : Scene(name), renderer(renderer), updater(updater)
{
}

void Unknown::CustomScene::render() const
{
    this->renderer();
}

void Unknown::CustomScene::update()
{
    this->updater();
}
