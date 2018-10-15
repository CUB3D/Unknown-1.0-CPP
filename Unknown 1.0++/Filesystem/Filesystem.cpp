//
// Created by cub3d on 10/10/18.
//

#include "Filesystem.h"

#include <istream>
#include <fstream>
#include <memory>

#include "PAKFileStream.h"

Unknown::Filesystem &Unknown::Filesystem::getFS() {
    static Filesystem fs;
    return fs;
}

void Unknown::Filesystem::mount(const std::string &path) {
    PAKFile pak;
    readPak(&pak, path.c_str());
    getFS().mounts.push_back(pak);
}

void Unknown::Filesystem::alias(const std::string &src, const std::string &dest) {

}

bool Unknown::Filesystem::exists(const std::string &str) {
    return false;
}

std::shared_ptr<std::istream> Unknown::Filesystem::readFile(const std::string &path) {

    auto file = std::make_shared<std::ifstream>(path);

    if(file->good()) {
        return file;
    }

    // If there is no version on the filesystem, check the mounts
    for(auto& pak : getFS().mounts) {
        PAKFileEntry* file = getFileFromPath(&pak, path.c_str());
        // If the file exists
        if(file) {
            return std::make_shared<std::istream>(new PAKFileStream(&pak, file));
        }
    }
}
