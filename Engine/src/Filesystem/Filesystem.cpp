//
// Created by cub3d on 10/10/18.
//

#include "Filesystem.h"

#include <istream>
#include <fstream>
#include <memory>

#include "PAKFileStream.h"
#include "Imemstream.h"
#include "core/log/Log.h"

Unknown::Filesystem &Unknown::Filesystem::getFS() {
    static Filesystem fs;
    return fs;
}

void Unknown::Filesystem::mount(const std::string &path) {
    PAKFile pak;
    readPak(&pak, path.c_str());
    getFS().mounts.push_back(pak);
    UK_INFO("Mounting '{}'", path.c_str());
}

void Unknown::Filesystem::alias(const std::string &src, const std::string &dest) {

}

bool Unknown::Filesystem::exists(const std::string &str) {
    return false;
}

Unknown::File Unknown::Filesystem::readFile(const std::string &path) {

    auto file = std::make_shared<std::ifstream>(path, std::ios::binary);

    if(file->good()) {
        return File(file);
    } else {
        UK_INFO("File '{}' not on system, looking in mounts", path);
    }

    // If there is no version on the filesystem, check the mounts
    for(auto& pak : getFS().mounts) {
        PAKFileEntry* file = getFileFromPath(&pak, path.c_str());
        // If the file exists
        if(file) {
            return File(std::make_shared<imemstream>(&pak, file));
        }
    }

    UK_ERROR("file '{}' not found", path.c_str());

    return File(nullptr);
}
