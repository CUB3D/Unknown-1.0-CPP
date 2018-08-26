//
// Created by cub3d on 14/08/18.
//

#include "RenderTestScene.h"
#include "UI2D.h"

#include "GL/GL.h"
#include "Graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//Unknown::Graphics::Image img("Player.png");

//std::shared_ptr<Unknown::Graphics::TTFont> font_;
//std::shared_ptr<StaticText> tex;

// TODO: make this initable
Shader s;

// TODO: create a setup script that will install the repo packages on linux and dl + extract the zips for libs on win as well as build box2d, will fix above

void RenderTestScene::render() const {

    if(s.prog == -1) {
        s.compile();
        printf("Compiling shader\n");
    }

    auto& uk = ::Unknown::getUnknown();

    float x = 0, y = 0, width = 1024, height = 1024;

    static float angle = 0;
    angle += 0.0001;
//

    int centerX = width / 2;
    int centerY = height / 2;

    s.bind();

    //TODO: move the matrix stuff to a helper func
    // Create the ortagonal projection
    glm::mat4 projection = glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(x + centerX, y + centerY, 0.0f));

    // Create the model matrix
    glm::mat4 modelView = view * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
    modelView = modelView * glm::translate(glm::mat4(1.0f), glm::vec3(-centerX, -centerY, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projection * modelView;

    //TODO: better way of setting uniforms
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "projmat"), 1, GL_FALSE, &proj[0][0]);

    //::Unknown::Graphics::drawVerticies(GL_TRIANGLES, verticies, VERTEX_COUNT, x, y, centerX, centerY, angle, UK_COLOUR_RGB(255, 0, 0));


    glUniform4f(glGetUniformLocation(s.prog, "inputColour"), 0, 0, 0, 1);

    // TODO: make this work in webgl
    UK_DRAW_RECT(0, 0, 1024, 1024, 0, UK_COLOUR_RGB(255, 0, 0));


    x = 100;
    y = 100;
    width = 100;
    height = 100;

    centerX = width / 2;
    centerY = height / 2;


    // Create the ortagonal projection
    projection = glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    view = glm::translate(glm::mat4(1), glm::vec3(x + centerX, y + centerY, 0.0f));

    // Create the model matrix
    modelView = view * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));
    modelView = modelView * glm::translate(glm::mat4(1.0f), glm::vec3(-centerX, -centerY, 0.0f));

    // Projection * view * model
    proj = projection * modelView;

    glUniformMatrix4fv(glGetUniformLocation(s.prog, "projmat"), 1, GL_FALSE, &proj[0][0]);

    glUniform4f(glGetUniformLocation(s.prog, "inputColour"), 1, 0, 0, 1);

    UK_DRAW_RECT(x, y, width, height, angle, UK_COLOUR_RGB(255, 0, 0));

    s.unbind();





















//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
//    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
//
//    glEnable(GL_DEPTH_TEST);
//
//    static double angle = 0;
//    angle = fmod((angle + 0.01), 360.0);
//
//
//    //glRotated(3, 1, 0, 0);
//
//    // Render a color-cube consisting of 6 quads with different colors
//    glLoadIdentity();                 // Reset the model-view matrix
//    //glRotated(45, 0, 0, 1);
//    glTranslated(1.5, 1.5, -1.4);
//    glRotated(angle, 1, 1, 1);
//
//    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
//    // Top face (y = 1.0f)
//    // Define vertices in counter-clockwise (CCW) order with normal pointing out
//    glColor3f(0.0f, 1.0f, 0.0f);     // Green
//    glVertex3f( 1.0f, 1.0f, -1.0f);
//    glVertex3f(-1.0f, 1.0f, -1.0f);
//    glVertex3f(-1.0f, 1.0f,  1.0f);
//    glVertex3f( 1.0f, 1.0f,  1.0f);
//
//    // Bottom face (y = -1.0f)
//    glColor3f(1.0f, 0.5, 0.0f);     // Orange
//    glVertex3f( 1.0f, -1.0f,  1.0f);
//    glVertex3f(-1.0f, -1.0f,  1.0f);
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glVertex3f( 1.0f, -1.0f, -1.0f);
//
//    // Front face  (z = 1.0f)
//    glColor3f(1.0f, 0.0f, 0.0f);     // Red
//    glVertex3f( 1.0f,  1.0f, 1.0f);
//    glVertex3f(-1.0f,  1.0f, 1.0f);
//    glVertex3f(-1.0f, -1.0f, 1.0f);
//    glVertex3f( 1.0f, -1.0f, 1.0f);
//
//    // Back face (z = -1.0f)
//    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
//    glVertex3f( 1.0f, -1.0f, -1.0f);
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glVertex3f(-1.0f,  1.0f, -1.0f);
//    glVertex3f( 1.0f,  1.0f, -1.0f);
//
//    // Left face (x = -1.0f)
//    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//    glVertex3f(-1.0f,  1.0f,  1.0f);
//    glVertex3f(-1.0f,  1.0f, -1.0f);
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glVertex3f(-1.0f, -1.0f,  1.0f);
//
//    // Right face (x = 1.0f)
//    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
//    glVertex3f(1.0f,  1.0f, -1.0f);
//    glVertex3f(1.0f,  1.0f,  1.0f);
//    glVertex3f(1.0f, -1.0f,  1.0f);
//    glVertex3f(1.0f, -1.0f, -1.0f);
//    glEnd();  // End of drawing color-cube

//auto& uk = ::Unknown::getUnknown();

//    if(s.prog == -1)
//        s.compile();

    //s.bind();

    // for(int i =0 i < 80; i+=8)
//    for(int i = 0; i < 10; i++) {




 //   }
//        Unknown::Graphics::drawCircle(50, 15 * i, 15, UK_COLOUR_RGB(0, 255, 0));
//        img.render(70, 50 * i);
//        tex->render(150, 50*i);
//    }
}

RenderTestScene::RenderTestScene() : Scene("RTest") {
    //font_ = std::make_shared<Unknown::Graphics::TTFont>("Fonts/Arimo-Regular.ttf", 14, Unknown::Colour::BLUE);
    //tex = std::make_shared<StaticText>(*font_, "Hello, World");
}
