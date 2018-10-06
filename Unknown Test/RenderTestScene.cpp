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
#include "KeyBind.h"
#include "Input.h"
#include "Graphics/SkyBox3D.h"

Unknown::Graphics::Image img("Player.png");

std::vector<aiMesh*> meshes;

void p1(aiNode* node, const aiScene* sce) {
    for(int i = 0; i < node->mNumMeshes; i++) {
        meshes.push_back(sce->mMeshes[i]);
    }

    for(int i = 0; i < node->mNumChildren; i++) {
        p1(node->mChildren[i], sce);
    }
}


std::vector<Unknown::TextureInfo> loadMaterialTexutres(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Unknown::TextureInfo> vec;


    for(int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string s = std::string(str.C_Str());
        s = "/home/cub3d/Downloads/nano/" + s;
        vec.push_back(Unknown::getRendererBackend()->loadTexture(s));
    }

    return vec;
}

Unknown::TextureInfo t;
Unknown::TextureInfo specular;

RenderingPipeline3D ren;

void init___() {
    std::vector<std::string> faces {
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg"
    };

    ren.init();

    ren.skybox = new SkyBox3D(faces);
    ren.skybox->init();

    MeshContainer mc;

    Assimp::Importer importer;
    const char* teapot = "teapot.obj";
    const char* ns = "/home/cub3d/Downloads/nano/nanosuit.obj";
    const char* suz = "Suz.obj";
    const char* uv = "uv.obj";
    const char* stick = "stick.obj";
    //const char* block = "block.obj";
    auto scene = importer.ReadFile(teapot, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes);

    std::string texPath = "teapot-texture.jpg";
    //texPath = "tree.jpg";
    //texPath = "wood-texture.jpg";
    texPath = "/home/cub3d/Downloads/crate.png";

    t = Unknown::getRendererBackend()->loadTexture(texPath);

    std::string specPath = "/home/cub3d/Downloads/crate_spec.png";
    specular = Unknown::getRendererBackend()->loadTexture(specPath);

    p1(scene->mRootNode, scene);

    printf("Found %d meshes\n", meshes.size());

    for(auto& mesh : meshes) {
        Mesh m;
        printf("Found %d verticies\n", mesh->mNumVertices);
        for(int i = 0; i < mesh->mNumVertices; i ++) {

            auto v = mesh->mVertices[i];
            m.verticies.emplace_back(v.x, v.y, v.z);

            if(mesh->HasNormals()) {
                auto n = mesh->mNormals[i];
                m.normals.emplace_back(n.x, n.y, n.z);
            }

            if(mesh->mTextureCoords[0]) {
                auto t = mesh->mTextureCoords[0][i];
                m.uvs.emplace_back(t.x, t.y);
            } else {
                m.uvs.emplace_back(0.0f, 0.0f);
            }
        }

        for(int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for(int j = 0; j < face.mNumIndices; j++) {
                m.indicies.push_back(face.mIndices[j]);
            }
        }
        // Check for materials
        //TODO: remove
        if(mesh->mMaterialIndex >= 0 && false) {
            aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Unknown::TextureInfo> diffuseMaps = loadMaterialTexutres(mat, aiTextureType_DIFFUSE, "texture_diffuse");
            std::vector<Unknown::TextureInfo> specularMaps = loadMaterialTexutres(mat, aiTextureType_SPECULAR, "texture_specular");
        }

        printf("Found %d indicies\n", m.indicies.size());

        mc.meshes.push_back(m);
    }

    mc.loadVBO();

    ren.meshes.push_back(std::make_shared<TexturedMeshRenderer>(mc));
}

Unknown::KeyBind forward(SDLK_w, "fw");
Unknown::KeyBind back(SDLK_s, "fs");
Unknown::KeyBind left(SDLK_a, "fw");
Unknown::KeyBind right(SDLK_d, "fd");

void RenderTestScene::update() {
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if(forward.pressed()) {
        ren.getCamera().forwards();
    }

    if(back.pressed()) {
        ren.getCamera().backwards();
    }

    if(left.pressed()) {
        ren.getCamera().left();
    }

    if(right.pressed()) {
        ren.getCamera().right();
    }

    ren.getCamera().onMouseMove();
}

bool tmp = false;



void RenderTestScene::render() const {
    //glClearColor(0, 0, 0, 1);
    //glClearDepth(1);
    //glEnable(GL_DEPTH_TEST);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // Draw skybox
    // TODO: j



    // Draw model
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, (GLuint)t.pointer);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, (GLuint)specular.pointer);

    ren.render();
}

RenderTestScene::RenderTestScene() : Scene("RTest") {
    init___();
}
