//
// Created by cub3d on 26/08/18.
//

#include "SDLBackend.h"

#include <SDL.h>

#include <Unknown.h>
#include <SDL_image.h>

void Unknown::SDLBackend::drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) {
    auto& uk = getUnknown();

    setColour(uk, colour);

    SDL_Rect rect{x, y, width, height};

    //TODO: err handling
    SDL_RenderFillRect(uk.windowRenderer, &rect);
}

void Unknown::SDLBackend::drawPoint(const int x, const int y, const Colour &colour) {
    auto& uk = getUnknown();

    setColour(uk, colour);

    SDL_RenderDrawPoint(uk.windowRenderer, x, y);
}

void Unknown::SDLBackend::setColour(Unknown &uk, const Colour &colour) {
    SDL_SetRenderDrawColor(uk.windowRenderer, colour.red, colour.green, colour.blue, colour.alpha);
}

void Unknown::SDLBackend::drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) {
    auto& uk = getUnknown();

    setColour(uk, col);

    SDL_RenderDrawLine(uk.windowRenderer, sx, sy, ex, ey);
}

void Unknown::SDLBackend::drawCircle(const int cx, const int cy, const int radius, const Colour &col) {
    auto& uk = getUnknown();

    setColour(uk, col);

    constexpr int vertexCount = 100;

    SDL_Point verts[vertexCount];

    float theta = 2 * 3.1415926 / float(vertexCount);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = radius;
    float y = 0;

    for (auto &vert : verts) {
        vert.x = x + cx;
        vert.y = y + cy;

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }


    SDL_RenderDrawLines(uk.windowRenderer, verts, vertexCount);
}

Unknown::TextureInfo Unknown::SDLBackend::loadTexture(const std::string &path) {
    auto find = textureMap.find(path);
    if(find != textureMap.end()) {
        return find->second;
    }

    auto& uk = getUnknown();

    SDL_Surface* image = IMG_Load(path.c_str());

    if(!image) {
        printf("Error: failed to load image, %s\n", IMG_GetError());
        uk.quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(uk.windowRenderer, image);

    TextureInfo info = {image->w, image->h, nullptr, (unsigned long long int) texture};
    textureMap.insert(std::pair<std::string, TextureInfo>(path, info));

    SDL_FreeSurface(image);

    return textureMap[path];
}

Unknown::VertexInfo Unknown::SDLBackend::createRectVerticies(const float x, const float y, const float w, const float h) {
    SDL_Rect r{(int)x, (int)y, (int)w, (int)h};
    auto& vertexInfo = vertexLookup.emplace_back();
    vertexInfo.bounds = r;

    return vertexInfo;
}

void Unknown::SDLBackend::renderTexture(const int x, const int y, const double angle, const TextureInfo &texture,
                                        const VertexInfo &verticies,
                                        const Dimension<float> renderSize) {
    auto& uk = getUnknown();
    SDL_Rect vert = verticies.bounds;
    vert.x = x;
    vert.y = y;
    SDL_RenderCopyEx(uk.windowRenderer, (SDL_Texture*)texture.pointer, NULL, &vert, angle, NULL, SDL_FLIP_NONE);
}

Unknown::TextureInfo Unknown::SDLBackend::createFontTexture(TTF_Font &font, const char *character,
                                                            const Colour &col) {
    TextureInfo& tex = fontLookup.emplace_back();

    // Draw char
    SDL_Surface* textSurface = TTF_RenderText_Blended(&font, character, col.toSDLColour());

    if(!textSurface) {
        printf("Unable to create texture for character '%c'\n", character);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(::Unknown::getUnknown().windowRenderer, textSurface);

    tex.width = textSurface->w;
    tex.height = textSurface->h;
    tex.pointer = (unsigned long long int) texture;

    SDL_FreeSurface(textSurface);

    return tex;
}

void Unknown::SDLBackend::clearScreen() {
    SDL_RenderClear(getUnknown().windowRenderer);
}

void Unknown::SDLBackend::intialise(const EngineConfig &config) {}

void Unknown::SDLBackend::createContext(SDL_Window *window) {}

void Unknown::SDLBackend::quit() {}

void Unknown::SDLBackend::newFrame() {}

void Unknown::SDLBackend::endFrame() {
    SDL_RenderPresent(getUnknown().windowRenderer);
}
