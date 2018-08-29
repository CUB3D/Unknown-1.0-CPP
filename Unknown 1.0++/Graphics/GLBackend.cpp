//
// Created by cub3d on 26/08/18.
//

#include "GLBackend.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../Utils.h"
#include "../Unknown.h"

void Unknown::GLBackend::drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) {

    if(shad.prog == -1)
        shad.compile();

    shad.bind();

    auto& uk = getUnknown();

    double centerX = width / 2.0;
    double centerY = height / 2.0;

    // Create the ortagonal projection
    glm::mat4 projection = glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(x + centerX, y + centerY, 0.0f));

    // Create the model matrix
    glm::mat4 modelView = view * glm::rotate(glm::mat4(1.0f), (float) angle, glm::vec3(0, 0, 1));
    modelView = modelView * glm::translate(glm::mat4(1.0f), glm::vec3(-centerX, -centerY, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projection * modelView;

    //TODO: better way of setting uniforms
    glUniformMatrix4fv(glGetUniformLocation(shad.prog, "projmat"), 1, GL_FALSE, &proj[0][0]);

    glUniform4f(glGetUniformLocation(shad.prog, "inputColour"), colour.red / 255.0, colour.green/255.0, colour.blue / 255.0, colour.alpha / 255.0);


    constexpr int VERTEX_COUNT = 18;

    float verticies[VERTEX_COUNT] =  {
        0, 0, 0,
        (float)width, 0, 0,
        0, (float)height, 0,

        0, (float)height, 0,
        (float)width, (float)height, 0,
        (float)width, 0, 0
    };

    glEnableClientState(GL_VERTEX_ARRAY);


    //TODO: first find some replacement for glVertexPointer, its not supported by webgl and it can't be emulated
//Also I think that client states are needed for native but not for emscripten

    glVertexPointer(3, GL_FLOAT, 0, verticies);
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);


    glDisableClientState(GL_VERTEX_ARRAY);

    shad.unbind();
}

Unknown::GLBackend::GLBackend() :  shad(FileShader("Vert.glsl", "Frag.glsl")) {

}
