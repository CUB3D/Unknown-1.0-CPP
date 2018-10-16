//
// Created by cub3d on 11/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_PAKFILESTREAM_H
#define UNKNOWN_DEVELOPMENT_TOOL_PAKFILESTREAM_H

#include <streambuf>
#include "LibPAK.h"

class PAKFileStream : public std::streambuf {
    PAKFileEntry* entry;

    char* buffer_;
    bool read;
public:
    PAKFileStream(PAKFile* file, PAKFileEntry* entry);

  //  ~PAKFileStream();
//
    //int underflow();
    virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode wich = std::ios_base::in) override;
    virtual pos_type seekpos(pos_type sp, std::ios_base::openmode which) override;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_PAKFILESTREAM_H
