//
// Created by cub3d on 14/08/18.
//

#include "RenderTestScene.h"
#include "UI2D.h"
#include "GL/GL.h"
#include "Graphics/FileShader.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model/MeshContainer.h"
#include "Graphics/RenderingPipeline3D.h"
#include "Model/TexturedMeshRenderer.h"
#include "Input/KeyBind.h"
#include "Input/Mouse.h"
#include "Graphics/SkyBox3D.h"
#include "Loader.h"

Unknown::Image img("Player.png");

RenderingPipeline3D ren;

#include "Filesystem/Filesystem.h"

void init___() {
    std::vector<std::string> faces {
        "skybox/right.jpg.png",
        "skybox/left.jpg.png",
        "skybox/top.jpg.png",
        "skybox/bottom.jpg.png",
        "skybox/front.jpg.png",
        "skybox/back.jpg.png"
    };

    ren.init();

    ren.skybox = new SkyBox3D(faces);
    ren.skybox->init();

    auto meshContainer = ::Unknown::Loader::loadModel("teapot.obj");
//    const char* teapot = "teapot.obj";
//    const char* ns = "nano/nanosuit.obj";
//    const char* suz = "Suz.obj";
//    const char* uv = "uv.obj";
//    const char* stick = "stick.obj";

    meshContainer->loadVBO();

    ren.meshes.push_back(std::make_shared<TexturedMeshRenderer>(*meshContainer));
}

Unknown::KeyBind forward(SDLK_w, "fw");
Unknown::KeyBind back(SDLK_s, "fs");
Unknown::KeyBind left2(SDLK_a, "fw");
Unknown::KeyBind right2(SDLK_d, "fd");

void RenderTestScene::update() {
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if(forward.pressed()) {
        ren.getCamera().forwards();
    }

    if(back.pressed()) {
        ren.getCamera().backwards();
    }

    if(left2.pressed()) {
        ren.getCamera().left();
    }

    if(right2.pressed()) {
        ren.getCamera().right();
    }

    ren.getCamera().onMouseMove();
}

void RenderTestScene::render() const {

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

    ren.render();
}

RenderTestScene::RenderTestScene() : Scene() {
    init___();
}
