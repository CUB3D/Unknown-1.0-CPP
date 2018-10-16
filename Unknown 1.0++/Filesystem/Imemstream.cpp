//
// Created by cub3d on 15/10/18.
//

#include "Imemstream.h"

imemstream::imemstream(PAKFile *pak, PAKFileEntry *ent) : PAKFileStream(pak, ent), std::istream(static_cast<std::streambuf*>(this)) {}
