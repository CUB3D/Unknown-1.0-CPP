//
// Created by cub3d on 03/10/18.
//

#include <cstdio>
#include "TexturedMeshRenderer.h"
#include "../Graphics/FileShader.h"
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>

TexturedMeshRenderer::TexturedMeshRenderer(MeshContainer &container) : MeshRenderer(container) {}

void TexturedMeshRenderer::render(Shader &s, RenderingPipeline3D &renderPipeline) {
    ZoneScopedN("TexturedMeshRenderer::Render");
    TracyGpuZone("TexturedMeshRenderer::Render");

    static float angle = 12;
    angle += 0.01;

    static float camX = 1.2f;
    camX+=0.001;

    if(camX > 3) {
        camX = 0;
    }

    static float camY = -2.0f;
    camY += 0.001;
    if(camY > 5)
        camY = -2.0f;

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10));
    model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(0, 1, 0));

    glm::mat4 modelView = renderPipeline.getCamera().getViewMatrix() * model;

    // Projection * view * model
    glm::mat4 proj = renderPipeline.projectionMatrix * renderPipeline.getCamera().getViewMatrix() * model;

    glUniformMatrix4fv(glGetUniformLocation(s.prog, "MVP"), 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelMatrix"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelView"), 1, GL_FALSE, &modelView[0][0]);
    glUniform1i(glGetUniformLocation(s.prog, "mat.diffuse"), 0);
    glUniform1i(glGetUniformLocation(s.prog, "mat.specular"), 1);
    s.setFloat("mat.shine", 32.0f);

    this->meshes.render();
}
