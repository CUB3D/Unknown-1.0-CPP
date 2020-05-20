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
#include <Graphics/RenderingBackend.h>
#include "Model/MeshContainer.h"
#include "Graphics/RenderingPipeline3D.h"
#include "Model/TexturedMeshRenderer.h"
#include "Input/KeyBind.h"
#include "Input/Mouse.h"
#include "Graphics/SkyBox3D.h"
#include "Loader.h"
#include <UK.h>

//Unknown::Image img("Player.png");

RenderingPipeline3D ren;

#include "Filesystem/Filesystem.h"

void init___() {
    std::vector<std::string> faces {
        "Assets/skybox/right.jpg",
        "Assets/skybox/left.jpg",
        "Assets/skybox/top.jpg",
        "Assets/skybox/bottom.jpg",
        "Assets/skybox/front.jpg",
        "Assets/skybox/back.jpg"
    };

    ren.init();

    ren.skybox = new SkyBox3D(faces);
    ren.skybox->init();

    printf("Loading teapot\n");
    auto meshContainer = ::Unknown::Loader::loadModel("Assets/model/backpack/backpack/backpack.obj");
    printf("Loading vbos\n");
    meshContainer->loadVBO();
    printf("mesh loading\n");
    ren.meshes.push_back(std::make_shared<TexturedMeshRenderer>(*meshContainer));
}

Unknown::KeyBind forward(SDLK_w, "fw");
Unknown::KeyBind back(SDLK_s, "fs");
Unknown::KeyBind left2(SDLK_a, "fw");
Unknown::KeyBind right2(SDLK_d, "fd");

void RenderTestScene::update() {
//    SDL_SetRelativeMouseMode(SDL_TRUE);

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

    //TODO: no better place to put the debugger
    if(ImGui::Begin("Camera3D")) {
        ImGui::SliderFloat("Speed", &ren.getCamera().cameraSpeed, 0.01, 1.0);
    }
    ImGui::End();

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

    ren.render();
}

RenderTestScene::RenderTestScene() : Scene() {
    init___();
}
