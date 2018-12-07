//
// Created by cub3d on 03/12/18.
//

#include <Renderer/BasicTileMapRenderer.h>
#include <Graphics/GLBackend.h>
#include "BasicGraphicsTest.h"
#include <tmxlite/Map.hpp>

UK::Image black("Assets/Black.png");
UK::Image white("Assets/White.png");

int width = 64;
int height = 64;
#define scaleX 8
#define scaleY 8

BasicGraphicsTest::BasicGraphicsTest() : Scene("BasicGraphics"), map(32, 32), timer(1.0f) {
    auto size = UK::Dimension<int>(8, 8);
    black.setDimentions(size);
    white.setDimentions(size);
    this->createBoard();
}

void BasicGraphicsTest::createBoard()
{
    tmx::Map map_;
    bool a = map_.load("/home/cub3d/Downloads/test.tmx");
    printf("Map load: %d\n", a);


    this->map = Unknown::Map(width, height);

    Unknown::BinaryMapGenerator().generate(map);

//    auto boardRenderer = std::make_shared<Unknown::BasicTileMapRenderer>(map, [](int x, int y, int id, int data) {
//            switch(id) {
//                case 0:
//                    black.render(x * scaleX, y * scaleY);
//                    break;
//                case 1:
//                    white.render(x * scaleX, y * scaleY);
//                    break;
//            }
//        }, false);
//    this->addObject(boardRenderer);
    //Unknown::getUnknown().globalSceneManager.getScene<Unknown::CustomScene>()->renderables.push_back(static_cast<std::shared_ptr<Unknown::IRenderable>>(boardRenderer));

//    auto& uk = Unknown::getUnknown();
//    scaleX = uk.screenSize->width / width;
//    scaleY = uk.screenSize->height / height;
}

std::vector<std::pair<UK::VertexInfo, std::pair<UK::TextureInfo, UK::Point<int>>>> i;

void BasicGraphicsTest::render() const {
    Scene::render();

    for(int x = 0; x < map.mapSize.width; x++) {
        for(int y = 0; y < map.mapSize.height; y++) {
            auto data = map.getTileID(x, y);

            switch(data) {
                case 0:
                    i.emplace_back(black.getVertexInfo(), std::pair<UK::TextureInfo, UK::Point<int>>(black.getTextureInfo(), UK::Point<int>(x * scaleX, y*scaleY)));
                    black.render(x * scaleX, y * scaleY);
                    break;
                case 1:
                    i.emplace_back(black.getVertexInfo(), std::pair<UK::TextureInfo, UK::Point<int>>(black.getTextureInfo(), UK::Point<int>(x * scaleX, y*scaleY)));
                    //white.render(x * scaleX, y * scaleY);
                    break;
            }
        }
    }

    static glm::mat4 projection = glm::ortho(0.0f, (float) 1024, (float) 1024, 0.0f, 0.0f, 1.0f);

    auto textureRenderer = std::dynamic_pointer_cast<UK::GLBackend>(UK::getRendererBackend())->getTextureRendererShader();
    textureRenderer.bind(true);

    for(auto& a : i) {
        float centerX = a.second.first.width / 2.0f;
        float centerY = a.second.first.height / 2.0f;

        // Create the model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(a.second.second.x + centerX, a.second.second.y + centerY, 0.0f));
        //model = glm::rotate(model, (float) glm::radians(0), glm::vec3(0, 0, 1.0f));
        model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));

        // Projection * view * model
        glm::mat4 proj = projection * model;

        glUniformMatrix4fv(glGetUniformLocation(textureRenderer.prog, "MVP"), 1, GL_FALSE, &proj[0][0]);
        glUniform1i(glGetUniformLocation(textureRenderer.prog, "texture0"), 0);

        glBindTexture(GL_TEXTURE_2D, (GLuint)a.second.first.pointer);

        glBindVertexArray(a.first.vao);

        // Render data
        //TODO: should store vertex count in vertexinfo
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    i.clear();
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
