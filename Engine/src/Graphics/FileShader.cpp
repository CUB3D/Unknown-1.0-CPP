//
// Created by cub3d on 26/08/18.
//

#include "FileShader.h"

#include <fstream>
#include <sstream>

FileShader::FileShader(const std::string &vert, const std::string &frag) : vertpath(vert), fragpath(frag) {
    std::stringstream tmp;

    std::ifstream vertFile(vert);

    if(vertFile.good()) {
        tmp << vertFile.rdbuf();
        this->vertexSrc = tmp.str();
        tmp.str(std::string());
    } else {
        printf("Failed to load vertex shader: %s\n", vert.c_str());
    }

    std::ifstream fragFile(frag);
    if(fragFile.good()) {
        tmp << fragFile.rdbuf();
        this->fragmentSrc = tmp.str();
    } else {
        printf("Failed to load fragment shader: %s\n", frag.c_str());
    }
}

std::string FileShader::getName() {
    return vertpath + ":" + fragpath;
}
