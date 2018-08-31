//
// Created by cub3d on 14/08/18.
//

#include "RenderTestScene.h"
#include "UI2D.h"

#include "GL/GL.h"
#include "Graphics/FileShader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Unknown::Graphics::Image img("Player.png");

//std::shared_ptr<Unknown::Graphics::TTFont> font_;
//std::shared_ptr<StaticText> tex;

FileShader s("ImageVert.glsl", "ImageFrag.glsl");

// TODO: make this initable

// TODO: create a setup script that will install the repo packages on linux and dl + extract the zips for libs on win as well as build box2d, will fix above


void RenderTestScene::render() const {
    auto& uk = ::Unknown::getUnknown();

    static float angle = 0;
    angle += 0.0001;

    //Fix flickering on windows
    // Move everyting to rendering backends
    // make core shaders part of src char[] etc
    // make all ui2d rendering batched and triangles
    // make ui2d circle just a scaled image embedded in src
    // add pak file support for better web fs support

    //UK_DRAW_RECT(0, 0, 1024, 1024, 0, UK_COLOUR_RGB(255, 0, 0));



    //UK_DRAW_RECT(100, 100, 100, 100, angle, UK_COLOUR_RGB(0, 255, 0));

    constexpr int x = 0, y = 0, width = 128, height = 128;

    constexpr double centerX = width / 2.0;
    constexpr double centerY = height / 2.0;

    //if(s.prog == -1) {
        //img = std::make_shared<Unknown::Graphics::Image>("Player.png");

        //s.compile();
        //s.bind();
   // }

   // s.bind();

    img.render(200, 200);

  //  s.unbind();

    ::Unknown::Graphics::drawPoint(10, 10, UK_COLOUR_RGB(255, 0, 0));

    ::Unknown::Graphics::drawLine(100, 100, 200, 200, UK_COLOUR_RGB(0, 255, 0));

    ::Unknown::Graphics::drawCircle(200, 200, 100, UK_COLOUR_RGB(0, 0, 255));

    //UK_DRAW_RECT(0, 0, 200, 200, 0, UK_COLOUR_RGB(255, 0, 0));























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
