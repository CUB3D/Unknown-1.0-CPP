//
// Created by cub3d on 28/11/18.
//

#include <Renderer/BasicTileMapRenderer.h>
#include "PathfindingTest.h"

#define M_SIZE ((1024/128))
#define M_SCALE  ((1024/M_SIZE))

PathfindingTest::PathfindingTest() : Scene(), m(M_SIZE, M_SIZE) {
    // Fill map with walls
    for(int x = 0; x < m.mapSize.width; x++) {
        for(int y = 0; y < m.mapSize.height; y++) {
            m(x, y) = 1;
        }
    }

    UK_ADD_MOUSE_LISTENER_EXTERNAL([&](UK::Event& evt) {
        auto pos = evt.mouse.location;
        m(pos.x/M_SCALE, pos.y/M_SCALE) = 0;
    }, "Test");

//    //------Gen maze------
//    // Pick rand cell, add walls to list
//    std::vector<UK::Point<int>> walls;
//    int SX = RANDINT(1, 255), SY = RANDINT(1, 255);
//    m(SX, SY) = 0; // Make path
//    walls.emplace_back(SX-1, SY);
//    walls.emplace_back(SX+1, SY);
//    walls.emplace_back(SX, SY-1);
//    walls.emplace_back(SX, SY+1);
//
//    while(!walls.empty()) {
//        int index = RANDINT(0, walls.size());
//        auto pnt = walls[index];
//
//        if(m(pnt.x + 1, pnt.y) == 0) {
//            if(m(pnt.x - 1, pnt.y) == 1) {
//                m(pnt.x - 1, pnt.y) = 0;
//
//                if(m(pnt.x+1, pnt.y) == 1)
//                    walls.emplace_back(pnt.x+1, pnt.y);
//
//                if(m(pnt.x, pnt.y-1) == 1)
//                    walls.emplace_back(pnt.x, pnt.y-1);
//
//                if(m(pnt.x, pnt.y+1) == 1)
//                    walls.emplace_back(pnt.x, pnt.y+1);
//
//                m(pnt.x, pnt.y) = 0;
//            }
//        } else {
//            if (m(pnt.x, pnt.y + 1) == 0) {
//                if (m(pnt.x, pnt.y - 1) == 1) {
//                    m(pnt.x, pnt.y - 1) = 0;
//
//                    if (m(pnt.x - 1, pnt.y) == 1)
//                        walls.emplace_back(pnt.x - 1, pnt.y);
//
//                    if (m(pnt.x + 1, pnt.y) == 1)
//                        walls.emplace_back(pnt.x + 1, pnt.y);
//
//                    if (m(pnt.x, pnt.y + 1) == 1)
//                        walls.emplace_back(pnt.x, pnt.y + 1);
//
//                     m(pnt.x, pnt.y) = 0;
//                }
//            }
//        }
//
//
//
//        walls.erase(walls.begin() + index);
//    }
}

void PathfindingTest::render() const {
    Scene::render();

    for(int x = 0; x < m.mapSize.width; x++) {
        for(int y = 0; y < m.mapSize.height; y++) {
            switch(m.getTileID(x, y)) {
                case 1: // Wall
                    UK_DRAW_SQUARE(x * M_SCALE, y * M_SCALE, M_SCALE, UK::BLACK);
                    break;
                case 0: // Path
                    UK_DRAW_SQUARE(x * M_SCALE, y * M_SCALE, M_SCALE, UK::WHITE);
                    break;
            }
        }
    }

    auto pos = UK::getMouseLocation();
    UK_DRAW_SQUARE((pos.x/M_SCALE)*M_SCALE, (pos.y/M_SCALE)*M_SCALE, M_SCALE, UK::RED);
}

void PathfindingTest::update() {
    Scene::update();
}
