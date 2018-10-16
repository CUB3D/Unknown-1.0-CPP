//
// Created by cub3d on 15/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_IMEMSTREAM_H
#define UNKNOWN_DEVELOPMENT_TOOL_IMEMSTREAM_H

#include "PAKFileStream.h"
#include <istream>

class imemstream : virtual PAKFileStream, public std::istream {
public:
    imemstream(PAKFile* pak, PAKFileEntry* ent);
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_IMEMSTREAM_H
