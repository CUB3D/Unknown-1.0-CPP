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

Unknown::Graphics::Image img("Player.png");

//std::shared_ptr<Unknown::Graphics::TTFont> font_;
//std::shared_ptr<StaticText> tex;

// TODO: make this initable

// TODO: create a setup script that will install the repo packages on linux and dl + extract the zips for libs on win as well as build box2d, will fix above

glm::mat4 glmhPerspectivef2(float fovyInDegrees, float aspectRatio,
                      float znear, float zfar)
{
    float ymax, xmax;
    float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    return glm::frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
}

class Mesh {
public:
    std::vector<glm::vec3> verticies;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indicies;

    GLuint vbo = 0;
    GLuint vao = 0;

    void loadVBO() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        int tmp = 3;

        if(normals.size() > 0)
            tmp += 3;

        if(uvs.size() > 0)
            tmp += 2;

        int SIZE = verticies.size() * (tmp);

        GLfloat* data = (GLfloat*) malloc(SIZE * sizeof(GLfloat));

        int x = 0;

        for(int i = 0; i < verticies.size(); i++) {
            auto &v = verticies[i];

            data[x++] = v.x;
            data[x++] = v.y;
            data[x++] = v.z;

            if(normals.size() > 0) {
                auto& n = normals[i];
                data[x++] = n.x;
                data[x++] = n.y;
                data[x++] = n.z;
            }

            if(uvs.size() > 0) {
                auto& uv = uvs[i];
                data[x++] = uv.x;
                data[x++] = uv.y;
            }
        }

        //TODO: sizeof float *
        glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat), data, GL_STATIC_DRAW);

        int stride = (tmp) * sizeof(GLfloat);

        int tmp2 = 3;

        // Verticies
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

        if(normals.size() > 0) {
            // Normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                                  reinterpret_cast<const void *>(tmp2 * sizeof(GLfloat)));
            tmp2 += 3;
        }

        if(uvs.size() > 0) {
            // UV's
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                                  reinterpret_cast<const void *>(tmp2 * sizeof(GLfloat)));
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render() {
        glBindVertexArray(vao);
//
//        unsigned int ind[indicies.size()];
//        for (int i = 0; i < indicies.size(); ++i) {
//            ind[i] = indicies[i];
//        }

        glDrawElements(GL_TRIANGLES, verticies.size(), GL_UNSIGNED_INT, &indicies[0]);
        glBindVertexArray(0);
    }
};

class MeshContainer {
public:
    std::vector<Mesh> meshes;

    void loadVBO() {
        printf("Gening %d vbos\n", meshes.size());
        for(auto& m : meshes) {
            m.loadVBO();
        }
    }

    void render() {
        for(auto& m : meshes) {
            m.render();
        }
    }
};



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

void init___() {
    Assimp::Importer importer;
    const char* glk = "/home/cub3d/Downloads/Glock/OBJ MTL/Glock 3d.obj";
    const char* bug = "/mnt/Data/Downloads/bugatti/bugatti.obj";
    const char* test = "Test.obj";
    const char* fourseven = "/home/cub3d/Downloads/obj/Handgun_obj.obj";
    const char* face = "/home/cub3d/Downloads/untitled.obj";
    const char* teapot = "teapot.obj";
    const char* ns = "/home/cub3d/Downloads/nano/nanosuit.obj";
    auto scene = importer.ReadFile(teapot, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes);

    std::string texPath = "teapot-texture.jpg";
    //texPath = "tree.jpg";

    t = Unknown::getRendererBackend()->loadTexture(texPath);

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
            }
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
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s.compile();
        s.bind();
        glBindTexture(GL_TEXTURE_2D, t.pointer);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float angle;
    angle += 0.1;

    // Create the ortagonal projection
    glm::mat4 projection = glmhPerspectivef2(45.0f, 1.0f, 0.1f, 100.0f);//glm::fru//glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10));
    model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(1, 0, 1));

    glm::mat4 modelView = view * model;

    // Projection * view * model
    glm::mat4 proj = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(s.prog, "MVP"), 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelMatrix"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelView"), 1, GL_FALSE, &modelView[0][0]);
    glUniform1i(glGetUniformLocation(s.prog, "texture0"), GL_TEXTURE0);


    mc.render();

   // s.unbind();
}

RenderTestScene::RenderTestScene() : Scene("RTest") {
    init___();
}
