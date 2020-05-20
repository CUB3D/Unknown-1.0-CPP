//
// Created by cub3d on 02/10/18.
//

#include "MeshContainer.h"

void MeshContainer::loadVBO() {
    for(auto& m : meshes) {
        m.loadVBO();
    }
}

void MeshContainer::render() {
    for(auto& m : meshes) {
        m.render();
    }
}
