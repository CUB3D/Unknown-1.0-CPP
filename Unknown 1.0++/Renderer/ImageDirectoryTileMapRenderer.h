//
// Created by cub3d on 11/07/2018.
//

#ifndef UNKNOWN_GAME_IMAGEDIRECTORYTILEMAPRENDERER_H
#define UNKNOWN_GAME_IMAGEDIRECTORYTILEMAPRENDERER_H

#include "BasicTileMapRenderer.h"
#include "Image.h"
#include <map>

namespace Unknown {
    class ImageDirectoryTileMapRenderer : public BasicTileMapRenderer {
        std::map<int, std::shared_ptr<::Unknown::Graphics::Image>> images;

    public:
        ImageDirectoryTileMapRenderer(Map &map1, std::string directory);
    };
}

#endif //UNKNOWN_GAME_IMAGEDIRECTORYTILEMAPRENDERER_H
