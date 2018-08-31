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
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT); // <- VERTEX count here hmmm, should it not be number of verticies (VERTEX_COUNT/3)


    glDisableClientState(GL_VERTEX_ARRAY);

    shad.unbind();

//    constexpr int VERTEX_COUNT = (3 + 4) * 6;
//
//    float r = colour.red / 255.0f;
//    float g = colour.green / 255.0f;
//    float b = colour.blue / 255.0f;
//    float a = colour.alpha / 255.0f;
//
//    float verticies[VERTEX_COUNT] =  {
//        // Format is x, y, z
//        // Then r, g, b, a
//        0, 0, 0,
//        r, g, b, a,
//
//        (float)width, 0, 0,
//        r, g, b, a,
//
//        0, (float)height, 0,
//        r, g, b, a,
//
//
//        0, (float)height, 0,
//        r, g, b, a,
//
//        (float)width, (float)height, 0,
//        r, g, b, a,
//
//        (float)width, 0, 0,
//        r, g, b, a
//    };
//
//    constexpr const int stride = (3 + 4) * sizeof(GLfloat);
//
//    glBindVertexArray(verticies);
//
//    // Verticies
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
//    // Colours
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>(3 * sizeof(GLfloat)));
//
//    glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);
//
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
}

Unknown::GLBackend::GLBackend() :  shad(FileShader("Vert.glsl", "Frag.glsl")) {

}

void Unknown::GLBackend::drawPoint(const int x, const int y, const Colour &colour) {
    if(shad.prog == -1)
        shad.compile();

    shad.bind();

    auto& uk = getUnknown();

    // Create the ortagonal projection
    glm::mat4 projection = glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(x, y, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projection * view * model;

    //TODO: better way of setting uniforms
    glUniformMatrix4fv(glGetUniformLocation(shad.prog, "projmat"), 1, GL_FALSE, &proj[0][0]);

    glUniform4f(glGetUniformLocation(shad.prog, "inputColour"), colour.red / 255.0, colour.green/255.0, colour.blue / 255.0, colour.alpha / 255.0);


    constexpr int VERTEX_COUNT = 3;

    float verticies[VERTEX_COUNT] =  {
        0, 0, 0,
    };

    glEnableClientState(GL_VERTEX_ARRAY);


    //TODO: first find some replacement for glVertexPointer, its not supported by webgl and it can't be emulated
//Also I think that client states are needed for native but not for emscripten

    glVertexPointer(3, GL_FLOAT, 0, verticies);
    glDrawArrays(GL_POINTS, 0, VERTEX_COUNT); // <- VERTEX count here hmmm, should it not be number of verticies (VERTEX_COUNT/3)


    glDisableClientState(GL_VERTEX_ARRAY);

    shad.unbind();
}

void Unknown::GLBackend::drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &colour) {
    if(shad.prog == -1)
        shad.compile();

    shad.bind();

    auto& uk = getUnknown();

    // Create the ortagonal projection
    glm::mat4 projection = glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(sx, sy, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projection * view * model;

    //TODO: better way of setting uniforms
    glUniformMatrix4fv(glGetUniformLocation(shad.prog, "projmat"), 1, GL_FALSE, &proj[0][0]);

    glUniform4f(glGetUniformLocation(shad.prog, "inputColour"), colour.red / 255.0, colour.green/255.0, colour.blue / 255.0, colour.alpha / 255.0);


    constexpr int VERTEX_COUNT = 6;

    int w = ex - sx;
    int h = ey - sy;

    float verticies[VERTEX_COUNT] =  {
        0, 0, 0,
        (float)w, (float)h, 0
    };

    glEnableClientState(GL_VERTEX_ARRAY);


    //TODO: first find some replacement for glVertexPointer, its not supported by webgl and it can't be emulated
//Also I think that client states are needed for native but not for emscripten

    glVertexPointer(3, GL_FLOAT, 0, verticies);
    glDrawArrays(GL_LINES, 0, VERTEX_COUNT); // <- VERTEX count here hmmm, should it not be number of verticies (VERTEX_COUNT/3)


    glDisableClientState(GL_VERTEX_ARRAY);

    shad.unbind();
}

void Unknown::GLBackend::drawCircle(const int cx, const int cy, const int radius, const Colour &colour) {
    if(shad.prog == -1)
        shad.compile();

    shad.bind();

    auto& uk = getUnknown();

    // Create the ortagonal projection
    glm::mat4 projection = glm::ortho(0.0f, (float) uk.screenSize->width, (float) uk.screenSize->height, 0.0f, 0.0f, 1.0f);

    // Create the view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(cx - radius, cy - radius, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projection * view * model;

    //TODO: better way of setting uniforms
    glUniformMatrix4fv(glGetUniformLocation(shad.prog, "projmat"), 1, GL_FALSE, &proj[0][0]);

    glUniform4f(glGetUniformLocation(shad.prog, "inputColour"), colour.red / 255.0, colour.green/255.0, colour.blue / 255.0, colour.alpha / 255.0);


    constexpr int segments = 100;

    constexpr int VERTEX_COUNT = 3 * segments;

    float verticies[VERTEX_COUNT];

    float theta = 2 * 3.1415926 / float(segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = radius;
    float y = 0;

    for(int ii = 0; ii < segments; ii++)
    {
        verticies[3 * ii + 0] = cx + x;
        verticies[3 * ii + 1] = cy + y;
        verticies[3 * ii + 2] = 0;

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }

    glEnableClientState(GL_VERTEX_ARRAY);


    //TODO: first find some replacement for glVertexPointer, its not supported by webgl and it can't be emulated
//Also I think that client states are needed for native but not for emscripten

    glVertexPointer(3, GL_FLOAT, 0, verticies);
    glDrawArrays(GL_LINES, 0, VERTEX_COUNT); // <- VERTEX count here hmmm, should it not be number of verticies (VERTEX_COUNT/3)


    glDisableClientState(GL_VERTEX_ARRAY);

    shad.unbind();
}

Unknown::TextureInfo Unknown::GLBackend::loadTexture(std::string &path) {
    auto find = textureMap.find(path);
    if(find != textureMap.end()) {
        return find->second;
    }


    auto& uk = getUnknown();

    SDL_Surface* imageSurface = IMG_Load(path.c_str());

    if (!imageSurface) {
        printf("Error: failed to load image, %s\n", IMG_GetError());
        uk.quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
    }

    textureMap.insert(std::pair<std::string, TextureInfo>(path, {imageSurface->w, imageSurface->h, 0}));
    auto& info = textureMap[path]; // The the object stored in the map

    glGenTextures(1, (GLuint*)&info.pointer);
    glBindTexture(GL_TEXTURE_2D, (GLuint)info.pointer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //how the texture should wrap in t direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //how the texture lookup should be interpolated when the face is smaller than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //how the texture lookup should be interpolated when the face is bigger than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);

    return info;
}

Unknown::VertexInfo Unknown::GLBackend::createRectVerticies(const int x, const int y, const int w, const int h) {
    auto& vertexInfo = vertexLookup.emplace_back();

    constexpr const int SIZE = 6 * (3 + 4 + 2 + 3);

    GLfloat data[SIZE] {
        // Format is vertex coord
        // Then colour
        // Then texcoord
        // Then normal
        0, 0, 0,
        1, 1, 1, 1,
        0, 0,
        0, 0, 1,

        (GLfloat)w, 0, 0,
        1, 1, 1, 1,
        1, 0,
        (GLfloat)w, 0, 1,

        (GLfloat)w, (GLfloat)h, 0,
        1, 1, 1, 1,
        1, 1,
        (GLfloat)w, (GLfloat)h, 1,

        0, 0, 0,
        1, 1, 1, 1,
        0, 0,
        0, 0, 1,

        0, (GLfloat)h, 0,
        1, 1, 1, 1,
        0, 1,
        0, (GLfloat)h, 1,

        (GLfloat)w, (GLfloat)h, 0,
        1, 1, 1, 1,
        1, 1,
        (GLfloat)w, (GLfloat)h, 1
    };

    glGenBuffers(1, &vertexInfo.vbo);

    // Bind VBO and put data in it
    glBindBuffer(GL_ARRAY_BUFFER, vertexInfo.vbo);
    glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat), data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexInfo.vao);

    // Bind the VAO and fill in the locations of each piece of vertex data
    glBindVertexArray(vertexInfo.vao);
    constexpr const int stride = (3 + 4 + 2 + 3) * sizeof(GLfloat); // Size of each sub block

    // Verticies
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
    // Colours
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>(3 * sizeof(GLfloat)));
    // Texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>((3 + 4) * sizeof(GLfloat)));
    // Normals
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>((3 + 4 + 2) * sizeof(GLfloat)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vertexInfo;
}

void
Unknown::GLBackend::renderTexture(const int x, const int y, const double angle, const TextureInfo &texture, const VertexInfo &verticies) {
    glBindTexture(GL_TEXTURE_2D, (GLuint)texture.pointer);

    glBindVertexArray(verticies.vao);

    // Render data
    //TODO: should store vertex count in vertexinfo
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind stuff
    glBindVertexArray(0);
}
