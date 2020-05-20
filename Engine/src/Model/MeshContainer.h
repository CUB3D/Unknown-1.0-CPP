//
// Created by cub3d on 02/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_MESHCONTAINER_H
#define UNKNOWN_DEVELOPMENT_TOOL_MESHCONTAINER_H

#include <vector>
#include "Mesh.h"

class MeshContainer {
public:
    std::vector<Mesh> meshes;

    void loadVBO();

    void render();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_MESHCONTAINER_H
