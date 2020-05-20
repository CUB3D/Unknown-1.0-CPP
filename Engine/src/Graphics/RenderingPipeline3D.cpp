//
// Created by cub3d on 03/10/18.
//

#include "RenderingPipeline3D.h"
#include "FileShader.h"
#include <GL/GL.h>
#include <Utils.h>
#include <Unknown.h>
#include <Imgui/GUI.h>
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>

void RenderingPipeline3D::render() {
    ZoneScopedN("RP3D::Render");
    TracyGpuZone("RP3D::Render");
    glClearColor(0, 0, 0, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    skybox->render(*this);

    s.bind(true);

//    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
//    memcpy(glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY), lightBuffer.data(), lightBuffer.size());
//    glUnmapBuffer(GL_UNIFORM_BUFFER);

    lm.updateLightBuffer();
    lm.updateBuffer();

    GLuint lightBlockIndex = glGetUniformBlockIndex(s.prog, "lighting");
    lm.bindBuffer(0);
//    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightUBO);
    glUniformBlockBinding(s.prog, lightBlockIndex, 0);

    // TODO: change to uniform blocks for lights
    s.setFloat("mat.diffuse", 0);
    s.setFloat("mat.specular", 1);
    s.setFloat("mat.shine", 32.0f);

    for(auto& mesh : meshes) {
        mesh->render(s, *this);
    }


//    ::ImGui::Begin("Test");
//    ::ImGui::Text("This is a test");
//
//    static bool edit;
//    ImGui::Checkbox("Edit", &edit);
//    ::ImGui::End();

//    glClearColor(1, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    //////TODO: Remove FBO (now done by backend) add this PIP to fbo debugger
//    //////TODO: Add RBO's to Framebuffer
//    if(edit) {
//        ImGui::SetNextWindowSize(ImVec2(512 + 10, 512 + 10),
//                                 ImGuiSetCond_FirstUseEver);
//        ImGui::Begin("Game rendering");
//        int w = 512;
//        int h = 512;
//
//        ImVec2 pos = ImGui::GetCursorScreenPos();
//
//        ImGui::GetWindowDrawList()->AddImage(
//            (void *)texBuffer, ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y),
//            ImVec2(pos.x + w, pos.y + h), ImVec2(0, 1), ImVec2(1, 0));
//        ImGui::End();
//    }
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
        UK_INFO("Invalid framebuffer");
    } else {
        UK_INFO("Framebuffer valid");
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



//    glGenBuffers(1, &lightUBO);
//    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
//    glBufferData(GL_UNIFORM_BUFFER, sizeof(lightBuffer), &lightBuffer, GL_DYNAMIC_DRAW);
//    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    lm.init();



    //this->fbov = Unknown::getRendererBackend()->createRectVerticies(-1, -1, 1, 1);
    //this->fbov = Unknown::getRendererBackend()->createRectVerticies(0, 0, uk.screenSize->width, uk.screenSize->height);
}
