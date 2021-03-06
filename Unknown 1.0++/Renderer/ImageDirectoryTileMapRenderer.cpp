//
// Created by cub3d on 11/07/2018.
//

#include "ImageDirectoryTileMapRenderer.h"
#include "../Map.h"
#include <filesystem>

Unknown::ImageDirectoryTileMapRenderer::ImageDirectoryTileMapRenderer(Unknown::Map &map1,
                                                                      std::string directory) : BasicTileMapRenderer(
        map1, nullptr, false) {
   std::filesystem::path dirPath = std::filesystem::u8path(directory);
   for(auto& p : std::filesystem::directory_iterator(dirPath)) {
       int id = 0;
       if(!Unknown::stringToInt(p.path().stem().string(), id)) {
           printf("Error converting %s to int at '%s':%d", p.path().stem().string(), __FILE__,__LINE__);
       }
       if(p.path().extension().string() != ".png") {
           printf("Found possible non image '%s', this could cause issues\n", p.path().extension().string().c_str());
       }
       printf("Loading %s\n", p.path().string().c_str());
       images[id] = std::make_shared<Graphics::Image>(p.path().string().c_str());//UK_LOAD_IMAGE(p.path().string().c_str());
   }

   this->renderer = [&](int x, int y, int id, int data) {
       auto img = images[id];
       if(img) {
           img->render(x * img->imageSize.width, y * img->imageSize.height);
       } else {
           printf("Error: no image for %d\n", id);
       }
   };
}
