//
// Created by cub3d on 03/10/18.
//

#include "RenderingPipeline3D.h"
#include "FileShader.h"
#include "../GL/GL.h"
#include "../Utils.h"
#include "../Unknown.h"

void RenderingPipeline3D::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(1, 0, 0, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    skybox->render(*this);


    s.bind(true);

    // TODO: change to uniform blocks for lights

    for(int i = 0; i < directionalLights.size(); i++) {
        std::string arr = "directionalLights[" + Unknown::intToString(i) + "]";

        s.setVec3((arr + ".ambient").c_str(), 0.1f, 0.1f, 0.1f);
        s.setVec3((arr + ".diffuse").c_str(), 0.3f, 0.3f, 0.3f);
        s.setVec3((arr + ".specular").c_str(), 1.0f, 1.0f, 1.0f);
        s.setVec3((arr + ".direction").c_str(), -0.2f, -1.0f, -0.3f);
    }
    // point

    for(int i = 0; i < pointLights.size(); i++) {
        std::string arr = "pointLights[" + Unknown::intToString(i) + "]";

        s.setVec3((arr + ".ambient").c_str(), 0.2f, 0.2f, 0.2f);
        s.setVec3((arr + ".diffuse").c_str(), 0.5f, 0.5f, 0.5f);
        s.setVec3((arr + ".specular").c_str(), 1.0f, 1.0f, 1.0f);
        s.setVec3((arr + ".position").c_str(), 1.0f, 2.0f, -9.0f);

        s.setFloat((arr + ".constant").c_str(), 1.0f);
        s.setFloat((arr + ".linear").c_str(), 0.09f);
        s.setFloat((arr + ".quadratic").c_str(), 0.032f);
    }

//    // spot
//
//    s.setVec3("spotlights[0].ambient", 0.2f, 0.2f, 0.2f);
//    s.setVec3("spotlights[0].diffuse", 0.5f, 0.5f, 0.5f);
//    s.setVec3("spotlights[0].specular", 1.0f, 1.0f, 1.0f);
//    s.setVec3("spotlights[0].position", 1.0f, 2.0f, 1.0f);
//
//    s.setVec3("spotlights[0].direction", 0, -1, 0);
//    s.setFloat("spotlights[0].cutOff", glm::cos(glm::radians(12.5f)));

    for(auto& mesh : meshes) {
        mesh->render(s, *this);
    }

    s.unbind();

    // Render the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    fboS.bind(true);
    glBindVertexArray(fbov.vao);
    glDisable(GL_DEPTH_TEST);
    fboS.setFloat("fboTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texBuffer);
    //glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

RenderingPipeline3D::RenderingPipeline3D() : s(FileShader("Test.glsl", "TestFrag.glsl")), fboS(FileShader("FBO_vert.glsl", "FBO_Frag.glsl")) {
    this->projectionMatrix = Unknown::glmhPerspectivef2(45.0f, 1.0f, 0.1f, 100.0f);
}

Camera3D &RenderingPipeline3D::getCamera() {
    return this->camera;
}

void RenderingPipeline3D::init() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    auto& uk = Unknown::getUnknown();

    glGenTextures(1, &texBuffer);
    glBindTexture(GL_TEXTURE_2D, texBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, uk.screenSize->width, uk.screenSize->height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texBuffer, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, uk.screenSize->width, uk.screenSize->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindBuffer(GL_RENDERBUFFER, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Invalid framebuffer\n");
    } else {
        printf("Framebuffer valid\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    constexpr const int SIZE = (2 + 2) * 6;

    float data[SIZE] = {
            -1, 1,
            0, 1,

            -1, -1,
            0, 0,

            1, -1,
            1, 0,


            -1, 1,
            0, 1,

            1, -1,
            1, 0,

            1, 1,
            1, 1

    };

    glGenBuffers(1, &fbov.vbo);

    glBindBuffer(GL_ARRAY_BUFFER, fbov.vbo);
    glBufferData(GL_ARRAY_BUFFER, SIZE*sizeof(GLfloat), data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &fbov.vao);
    glBindVertexArray(fbov.vao);

    constexpr const int STRIDE = (2 + 2) * sizeof(GLfloat);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, STRIDE, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE, reinterpret_cast<const void *>(2 * sizeof(GLfloat)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //this->fbov = Unknown::getRendererBackend()->createRectVerticies(-1, -1, 1, 1);
    //this->fbov = Unknown::getRendererBackend()->createRectVerticies(0, 0, uk.screenSize->width, uk.screenSize->height);
}
