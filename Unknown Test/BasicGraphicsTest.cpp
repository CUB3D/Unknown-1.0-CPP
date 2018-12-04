//
// Created by cub3d on 03/12/18.
//

#include <Renderer/BasicTileMapRenderer.h>
#include "BasicGraphicsTest.h"

UK::Image black("Assets/Black.png");
UK::Image white("Assets/White.png");

int width = 64;
int height = 64;
int scaleX = 0;
int scaleY = 0;

BasicGraphicsTest::BasicGraphicsTest() : Scene("BasicGraphics"), map(32, 32), timer(1.0f) {
    this->createBoard();
}

void BasicGraphicsTest::createBoard()
{
    this->map = Unknown::Map(width, height);

    Unknown::BinaryMapGenerator().generate(map);

    auto boardRenderer = std::make_shared<Unknown::BasicTileMapRenderer>(map, [](int x, int y, int id, int data) {
            switch(id) {
                case 0:
                    black.render(x * scaleX, y * scaleY);
                    UK_DRAW_RECT(x * scaleX, y * scaleY, scaleX, scaleY, UK::BLACK);
                    break;
                case 1:
                    UK_DRAW_RECT(x * scaleX, y * scaleY, scaleX, scaleY, UK::WHITE);
                    break;
            }
        }, false);
    this->addObject(boardRenderer);
    //Unknown::getUnknown().globalSceneManager.getScene<Unknown::CustomScene>()->renderables.push_back(static_cast<std::shared_ptr<Unknown::IRenderable>>(boardRenderer));

    auto& uk = Unknown::getUnknown();
    scaleX = uk.screenSize->width / width;
    scaleY = uk.screenSize->height / height;
}

void BasicGraphicsTest::render() const {
    Scene::render();
}

void BasicGraphicsTest::update() {
    Scene::update();

    UK::Map newMap(width, height);

    if (timer.isTickComplete()) {
        for (int x = 0; x <  map.mapSize.width; x++) {
            for (int y = 0; y <  map.mapSize.height; y++) {
                int alive = map.getTileID(x, y);
                int popcount = 0;
                popcount += checkTile(x - 1, y - 1, map);
                popcount += checkTile(x - 1, y, map);
                popcount += checkTile(x - 1, y + 1, map);

                popcount += checkTile(x, y - 1, map);
                popcount += checkTile(x, y + 1, map);

                popcount += checkTile(x + 1, y - 1, map);
                popcount += checkTile(x + 1, y, map);
                popcount += checkTile(x + 1, y + 1, map);

                if (alive) {
                    newMap(x, y) = !(popcount < 2 || popcount > 3);
                } else {
                    newMap(x, y) = (popcount == 3);
                }
            }
        }
        map = newMap;
    }
}

int BasicGraphicsTest::checkTile(int x, int y, UK::Map &map) {
    return map.isOnBoard(x, y) ? map(x, y) : 0;
}
