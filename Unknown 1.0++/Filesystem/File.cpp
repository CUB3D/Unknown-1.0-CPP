//
// Created by cub3d on 19/12/18.
//

#include "File.h"
#include <sstream>

Unknown::File::File(std::shared_ptr<std::istream> stream) : backendStream(stream) {}

std::shared_ptr<std::istream> Unknown::File::getStream() const {
    return this->backendStream;
}

bool Unknown::File::isGood() const {
    return this->backendStream != nullptr;
}

Unknown::File::operator bool() const {
    return isGood();
}

std::string Unknown::File::getString() const {
    std::stringstream ss;
    ss << getStream()->rdbuf();
    return ss.str();
}
