//
// Created by cub3d on 26/08/18.
//

#include "GLBackend.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Utils.h>
#include <Unknown.h>
#include <Filesystem/Filesystem.h>
#include <Filesystem/FSUtils.h>
#include <core/log/Log.h>
#include <Imgui/GUI.h>
#include "PlaceholderTexture.h"
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>

void Unknown::GLBackend::intialise(const EngineConfig& config) {
    UK_INFO("Intialising OpenGL Backend");
}

void Unknown::GLBackend::createContext(SDL_Window* window) {
    ZoneScopedN("GL::CreateContext");
    UK_INFO("Creating OpenGL 3.3 Core context");

    //TODO: abstract out windows from unknown
    auto& size = getUnknown().screenSize;

    // Enable GL3.3 Core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    this->glContext = SDL_GL_CreateContext(window);

    // Load glad, glfw, etc
    initGL();
    TracyGpuContext;

    // Setup gl viewport
    glViewport(0, 0, size.x, size.y);

    // Load Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    auto& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(size.x, size.y);

    basicRenderer.compile();
    textureRenderer.compile();
    FBOshader.compile();

    circleShader = new FileShader("Circle_vert.glsl", "Circle_frag.glsl");
    circleShader->compile();

    this->projectionMatrix = glm::ortho(0.0f, (float) size.x, (float) size.y, 0.0f, 0.0f, 1.0f);
    this->viewMatrix = glm::mat4(1.0f);

    //TODO: use ctrp to get view from camera(2D/3D)

    // Create FBO
    FBO.createFBO();
}

void Unknown::GLBackend::quit() {
    SDL_GL_DeleteContext(glContext);
}

void Unknown::GLBackend::drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) {
    VertexInfo info = this->createRectVerticies(0, 0, width, height);

    basicRenderer.bind();
    basicRenderer.setColour("inputColour", colour);
    this->renderQuad(x, y, angle, info, basicRenderer);

    deleteVerticies(info);
}

Unknown::GLBackend::GLBackend() :  basicRenderer(renderingVertexShader, renderingFragmentShader),
                                   textureRenderer(imageVertexShader, imageFragmentShader),
                                   FBO(getUnknown().config.targetSize),
                                   FBOshader(FBOVertexShader, FBOFragmentShader) {
}

void Unknown::GLBackend::drawPoint(const int x, const int y, const Colour &colour) {
    VertexInfo info = this->createRectVerticies(0, 0, 1, 1);

    basicRenderer.bind();
    basicRenderer.setColour("inputColour", colour);

    this->renderQuad(x, y, 0, info, basicRenderer);

    deleteVerticies(info);
}

void Unknown::GLBackend::drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &colour) {
    basicRenderer.bind();

    auto& uk = getUnknown();

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(sx, sy, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projectionMatrix * viewMatrix * model;

    basicRenderer.setMat4("projmat", proj);
    basicRenderer.setColour("inputColour", colour);

    int w = ex - sx;
    int h = ey - sy;

    auto& vertexInfo = vertexLookup.emplace_back();

    constexpr const int SIZE = 2 * (3);

    GLfloat data[SIZE] {
        // Format is vertex coord
        0, 0, 0,

        (GLfloat)w, (GLfloat) h, 0,
    };

    glGenBuffers(1, &vertexInfo.vbo);

    // Bind VBO and put data in it
    glBindBuffer(GL_ARRAY_BUFFER, vertexInfo.vbo);
    glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat), data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexInfo.vao);

    // Bind the VAO and fill in the locations of each piece of vertex data
    glBindVertexArray(vertexInfo.vao);
    constexpr const int stride = (3) * sizeof(GLfloat); // Size of each sub block

    // Verticies
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

    glDrawArrays(GL_LINES, 0, 2); // <- VERTEX count here hmmm, should it not be number of verticies (VERTEX_COUNT/3)

    deleteVerticies(vertexInfo);
}

void Unknown::GLBackend::drawCircle(const int cx, const int cy, const int radius, const Colour &colour) {
    ZoneScopedN("GL::drawCircle");
    auto& uk = getUnknown();


    circleShader->bind();
    circleShader->setColour("inputColour", colour);
    circleShader->setInt("radius", radius);
    circleShader->setVec2("centre", cx, uk.config.targetSize.y - cy);

    //TODO:
    VertexInfo info = this->createRectVerticies(0, 0, 1000, 1000);



    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(cx, cy, 0.0f));
    model = glm::rotate(model, (float) glm::radians(0.0f), glm::vec3(0, 0, 1.0f));
    model = glm::translate(model, glm::vec3(-cx, -cy, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projectionMatrix * viewMatrix * model;

    circleShader->setMat4("projmat", proj);

    glBindVertexArray(info.vao);

    // Render data
    //TODO: should store vertex count in vertexinfo
    glDrawArrays(GL_TRIANGLES, 0, 6);

    deleteVerticies(info);
}

Unknown::TextureInfo Unknown::GLBackend::loadTexture(const std::string &path) {
    ZoneScopedN("GL::loadTexture");
    auto find = textureMap.find(path);
    if(find != textureMap.end()) {
        return find->second;
    }

    auto& uk = getUnknown();

    auto file = Filesystem::readFile(path);

    SDL_Surface* imageSurface = nullptr;

    if(file) {
        imageSurface = IMG_Load_RW(getRWopsForStream(*file.getStream()), false);
	} else {
		UK_INFO("File '{}' not found", path.c_str());
	}

    if (!imageSurface) {
        UK_ERROR("failed to load image '{}': {}", path.c_str(), IMG_GetError());
        if(uk.config.textureFallback) {
            UK_INFO("Loading fallback");
            imageSurface = IMG_Load_RW(SDL_RWFromConstMem(placeholder_png, placeholder_png_len), false);
        }

        // Check again, will quit if either both image and fallback failed or if fallback disabled and load failed
        if(!imageSurface) {
            uk.quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
        }
    }

    textureMap.insert(std::pair<std::string, TextureInfo>(path, {imageSurface->w, imageSurface->h, 0}));
    auto& info = textureMap[path]; // The the object stored in the map

    glGenTextures(1, (GLuint*)&info.pointer);
    glBindTexture(GL_TEXTURE_2D, (GLuint)info.pointer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //how the texture should wrap in t direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //how the texture lookup should be interpolated when the face is smaller than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //how the texture lookup should be interpolated when the face is bigger than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //TODO: change to gl_nearest when using fallback texture

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

    info.pixelData = (unsigned char*)imageSurface->pixels;

    glTexImage2D(GL_TEXTURE_2D, 0, mode, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);


    return info;
}

Unknown::VertexInfo Unknown::GLBackend::createRectVerticies(const float x, const float y, const float w, const float h) {
    ZoneScopedN("GL::CreateRectVerticies");
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
        0, 0, -1,

        (GLfloat)w, 0, 0,
        1, 1, 1, 1,
        1, 0,
        0, 0, -1,

        (GLfloat)w, (GLfloat)h, 0,
        1, 1, 1, 1,
        1, 1,
        0, 0, -1,

        0, 0, 0,
        1, 1, 1, 1,
        0, 0,
        0, 0, -1,

        0, (GLfloat)h, 0,
        1, 1, 1, 1,
        0, 1,
        0, 0, -1,

        (GLfloat)w, (GLfloat)h, 0,
        1, 1, 1, 1,
        1, 1,
        0, 0, -1
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

    vertexInfo.vertexCount = 6;

    return vertexInfo;
}
//TODO: abstract rendering texture out from rendering quad
//TODO: should render functions not take radians,
// Most of the time angle is retrieve from physics which works in radians already
void Unknown::GLBackend::renderTexture(const int x, const int y, const double angle, const TextureInfo &texture,
                                       const VertexInfo &verticies,
                                       const glm::vec2 renderSize) {
    ZoneScopedN("GL::RenderTexture");
    TracyGpuZone("RenderTexture");
    auto& uk = getUnknown();

    float centerX = texture.width / 2.0f;
    float centerY = texture.height / 2.0f;

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x + centerX, y + centerY, 0.0f));
    model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(0, 0, 1.0f));
    model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));
    model = glm::scale(model, glm::vec3(renderSize.x, renderSize.y, 1.0));

    // Projection * view * model
    glm::mat4 proj = projectionMatrix * viewMatrix * model;

    textureRenderer.bind();

    //glUniformMatrix4fv(glGetUniformLocation(textureRenderer.prog, "MVP"), 1, GL_FALSE, &proj[0][0]);
    textureRenderer.setMat4("MVP", proj);
    textureRenderer.setInt("texture0", 0);

    glBindTexture(GL_TEXTURE_2D, (GLuint)texture.pointer);
    glBindVertexArray(verticies.vao);

    // Render data
    //TODO: should store vertex count in vertexinfo
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Unknown::TextureInfo Unknown::GLBackend::createFontTexture(TTF_Font &font, const char *str,
                                                           const Colour &col) {
    ZoneScopedN("GL::createFontTexture");
    TracyGpuZone("GL::createFontTexture");

    TextureInfo& tex = fontLookup.emplace_back();

    // Draw char
    SDL_Surface* textSurface = TTF_RenderText_Blended(&font, str, col.toSDLColour());

    if(!textSurface) {
        UK_INFO("Error: Failed to create surface");
        return tex;
    }

    // Convert to known format
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

//TODO: this causes the outline on the image, removing fixes it but would break compat with some archatectures
    SDL_Surface* tmp = SDL_CreateRGBSurface(0, textSurface->w, textSurface->h, 32, rmask, gmask, bmask, amask);
    SDL_BlitSurface(textSurface, NULL, tmp, NULL);

    int nOfColors = tmp->format->BytesPerPixel;
    int mode = GL_RGBA;
    if( nOfColors == 4 )     // contains an alpha channel
    {
        if(tmp->format->Rmask == 0x000000ff) {
            mode = GL_RGBA;
        } else {
            mode = GL_BGRA;
        }
    } else if( nOfColors == 3 ) {
        if(tmp->format->Rmask == 0x000000ff) {
            mode = GL_RGB;
        } else {
            mode = GL_BGR;
        }
    }

    // Copy to gpu
    glGenTextures(1, (GLuint*)&tex.pointer);
    glBindTexture(GL_TEXTURE_2D, tex.pointer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //how the texture should wrap in t direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //how the texture lookup should be interpolated when the face is smaller than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //how the texture lookup should be interpolated when the face is bigger than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textSurface->w, textSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmp->pixels);
    tex.width = textSurface->w;
    tex.height = textSurface->h;

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(tmp);

    return tex;
}

void Unknown::GLBackend::clearScreen() {
    ZoneScopedN("GL::clearScreen");
    TracyGpuZone("GL::clearScreen");
    // TODO: need a setup function for the backends, also put glv
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//TODO: some bug here to do with positioning, or in basicrendercomponent
void Unknown::GLBackend::renderQuad(const int x, const int y, const double angle, const VertexInfo &verts, Shader& shader) {
    ZoneScopedN("GL::renderQuad");
    TracyGpuZone("GL::renderQuad");

    auto& uk = getUnknown();

    float centerX = verts.bounds.w / 2.0f;
    float centerY = verts.bounds.h / 2.0f;

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x + centerX, y + centerY, 0.0f));
    model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(0, 0, 1.0f));
    model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projectionMatrix * viewMatrix * model;

    shader.setMat4("projmat", proj);

    glBindVertexArray(verts.vao);

    // Render data
    //TODO: should store vertex count in vertexinfo
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Shader &Unknown::GLBackend::getTextureRendererShader() {
    return this->textureRenderer;
}

/**
 * Delete the vertex info provided, use of paramter after calling is UB
 * info.VAO/VBO will = 0 after this operation
 * @param info The vertex info to remove
 */
void Unknown::GLBackend::deleteVerticies(VertexInfo& info) {
    ZoneScopedN("GL::deleteVerticies");
    TracyGpuZone("GL::deleteVerticies");

    vertexLookup.erase(std::remove_if(vertexLookup.begin(), vertexLookup.end(), [&](VertexInfo& it) {
        return it.vao == info.vao && it.vbo == info.vbo;
    }));

    glDeleteVertexArrays(1, &info.vao);
    glDeleteBuffers(1, &info.vbo);

    info.vao = 0;
    info.vbo = 0;
}

void Unknown::GLBackend::newFrame() {
    ZoneScopedN("GL::newFrame");
    TracyGpuZone("GL::newFrame");
    FBO.bind();
}

void Unknown::GLBackend::endFrame() {
    ZoneScopedN("GL::endFrame");
    TracyGpuZone("GL::endFrame");


//    glEnable(GL_FRAMEBUFFER_SRGB);
    FBO.unbind();

    FBOshader.setFloat("fboTexture", 0);
    FBO.render(FBOshader);
//    glDisable(GL_FRAMEBUFFER_SRGB);

    {
        ZoneScopedN("GL::SwapWindow");
        SDL_GL_SwapWindow(getUnknown().windowManager.window);
    }
    TracyGpuCollect;
}
