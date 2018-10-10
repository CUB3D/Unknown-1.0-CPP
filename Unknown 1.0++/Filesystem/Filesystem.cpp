//
// Created by cub3d on 10/10/18.
//

#include "Filesystem.h"

Unknown::Filesystem &Unknown::Filesystem::getFS() {
    static Filesystem fs;
    return fs;
}
