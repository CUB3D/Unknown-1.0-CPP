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

Unknown::Graphics::Image img("Player.png");

// Cubemap stuff

GLuint loadCubeMap(std::vector<std::string>& faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for(int i = 0; i < faces.size(); i++) {
        printf("Loading %s\n", faces[i].c_str());

        SDL_Surface* imageSurface = IMG_Load(faces[i].c_str());

        if (!imageSurface) {
            printf("Error: failed to load image, %s\n", IMG_GetError());
            return 0;
        }

        int nOfColors = imageSurface->format->BytesPerPixel;
        int mode = GL_RGBA;
        if( nOfColors == 4 )     // contains an alpha channel
        {
            if(imageSurface->format->Rmask == 0x000000ff) {
                mode = GL_RGBA;
            } else {
                mode = GL_BGRA;
            }
        } else if( nOfColors == 3 ) {
            if(imageSurface->format->Rmask == 0x000000ff) {
                mode = GL_RGB;
            } else {
                mode = GL_BGR;
            }
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);

        SDL_FreeSurface(imageSurface);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
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

GLuint cubemap;
GLuint cubeMapVAO;
GLuint cubeMapVBO;

FileShader sky("Sky_vert.glsl", "Sky_frag.glsl");



void init___() {
    std::vector<std::string> faces {
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg"
    };
    cubemap = loadCubeMap(faces);

    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    glGenBuffers(1, &cubeMapVBO);

    // Bind VBO and put data in it
    glBindBuffer(GL_ARRAY_BUFFER, cubeMapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &cubeMapVAO);

    // Bind the VAO and fill in the locations of each piece of vertex data
    glBindVertexArray(cubeMapVAO);

    // Verticies
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


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

void RenderTestScene::update() {
}

bool tmp = false;

void RenderTestScene::render() const {
    glClearColor(0, 0, 0, 1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // Draw skybox
    glDepthMask(GL_FALSE);
    sky.bind(true);
    sky.setFloat("skybox", 0);
    glUniformMatrix4fv(glGetUniformLocation(sky.prog, "proj"), 1, GL_FALSE, &ren.projectionMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(sky.prog, "view"), 1, GL_FALSE, &glm::mat4(glm::mat3(ren.viewMatrix))[0][0]);
    glBindVertexArray(cubeMapVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    sky.unbind();



    // Draw model
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, (GLuint)t.pointer);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, (GLuint)specular.pointer);

    glEnable(GL_MULTISAMPLE);

    ren.render();
}

RenderTestScene::RenderTestScene() : Scene("RTest") {
    init___();
}
