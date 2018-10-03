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

Unknown::Graphics::Image img("Player.png");

glm::mat4 glmhPerspectivef2(float fovyInDegrees, float aspectRatio,
                      float znear, float zfar)
{
    float ymax, xmax;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    xmax = ymax * aspectRatio;
    return glm::frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
}



std::vector<aiMesh*> meshes;

void p1(aiNode* node, const aiScene* sce) {
    for(int i = 0; i < node->mNumMeshes; i++) {
        meshes.push_back(sce->mMeshes[i]);
    }

    for(int i = 0; i < node->mNumChildren; i++) {
        p1(node->mChildren[i], sce);
    }
}



MeshContainer mc;
Unknown::TextureInfo t;
Unknown::TextureInfo specular;

void init___() {
    Assimp::Importer importer;
    const char* glk = "/home/cub3d/Downloads/Glock/OBJ MTL/Glock 3d.obj";
    const char* bug = "/mnt/Data/Downloads/bugatti/bugatti.obj";
    const char* test = "Test.obj";
    const char* fourseven = "/home/cub3d/Downloads/obj/Handgun_obj.obj";
    const char* face = "/home/cub3d/Downloads/untitled.obj";
    const char* teapot = "teapot.obj";
    const char* ns = "/home/cub3d/Downloads/nano/nanosuit.obj";
    const char* suz = "Suz.obj";
    const char* uv = "uv.obj";
    const char* stick = "stick.obj";
    auto scene = importer.ReadFile(stick, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes);

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

            printf("UV: %d\n", mesh->GetNumUVChannels());
        }

        for(int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for(int j = 0; j < face.mNumIndices; j++) {
                m.indicies.push_back(face.mIndices[j]);
            }
        }

        printf("Found %d indicies\n", m.indicies.size());

        mc.meshes.push_back(m);
    }

    mc.loadVBO();
}

FileShader s("Test.glsl", "TestFrag.glsl");

void RenderTestScene::update() {
}

bool tmp = false;

void RenderTestScene::render() const {
    if(s.prog == -1) {

        glClearColor(0, 0, 0, 1);
        glClearDepth(1);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s.compile();
        s.bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (GLuint)t.pointer);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, (GLuint)specular.pointer);

        glEnable(GL_MULTISAMPLE);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float angle = 12;
    angle += 0.01;

    static float camX = 1.2f;
    camX+=0.001;

    if(camX > 10) {
        camX = 0;
    }

    static float camY = -2.0f;
    camY += 0.001;
    if(camY > 10)
        camY = -2.0f;

    // Create the projection matrix
    glm::mat4 projection = glmhPerspectivef2(45.0f, 1.0f, 0.1f, 100.0f);//glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1, -1, -12));
    model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(0, 1, 0));

    glm::mat4 modelView = view * model;

    // Projection * view * model
    glm::mat4 proj = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(s.prog, "MVP"), 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelMatrix"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelView"), 1, GL_FALSE, &modelView[0][0]);
    glUniform1i(glGetUniformLocation(s.prog, "mat.diffuse"), GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(s.prog, "mat.specular"), GL_TEXTURE1);

    s.setVec3("mat.ambient", 1.0f, 0.5f, 0.31f);
    s.setVec3("mat.diffuse", 1.0f, 0.5f, 0.31f);
    s.setVec3("mat.specular", 0.5f, 0.5f, 0.5f);
    s.setFloat("mat.shine", 32.0f);

    s.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    s.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    s.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    s.setVec3("light.position", camX, -1.0f, camY);

    mc.render();

   // s.unbind();
}

RenderTestScene::RenderTestScene() : Scene("RTest") {
    init___();
}
