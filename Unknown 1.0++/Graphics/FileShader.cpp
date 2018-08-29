//
// Created by cub3d on 26/08/18.
//

#include "FileShader.h"

#include <fstream>
#include <sstream>

FileShader::FileShader(const std::string &vert, const std::string &frag) {
    std::stringstream tmp;

    std::ifstream vertFile(vert);
    tmp << vertFile.rdbuf();
    this->vertexSrc = tmp.str();
    tmp.str(std::string());

    std::ifstream fragFile(frag);
    tmp << fragFile.rdbuf();
    this->fragmentSrc = tmp.str();
}
