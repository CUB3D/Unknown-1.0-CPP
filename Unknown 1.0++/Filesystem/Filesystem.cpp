//
// Created by cub3d on 10/10/18.
//

#include "Filesystem.h"

#include <SDL2/SDL.h>

Unknown::Filesystem &Unknown::Filesystem::getFS() {
    static Filesystem fs;
    return fs;
}

void Unknown::Filesystem::mount(const std::string &path) {
}

void Unknown::Filesystem::alias(const std::string &src, const std::string &dest) {

}

bool Unknown::Filesystem::exists(const std::string &str) {
    return false;
}
