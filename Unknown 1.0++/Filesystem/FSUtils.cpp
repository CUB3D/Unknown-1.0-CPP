//
// Created by cub3d on 11/10/18.
//

#include "FSUtils.h"

SDL_RWops* getRWopsForStream(std::istream& stream) {
    SDL_RWops* ops = SDL_AllocRW();

    ops->read = &istreamRead;
    ops->seek = &istreamSeek;
    ops->close = istreamClose;
    ops->write = nullptr; //TODO
    ops->hidden.unknown.data1 = &stream;

    return ops;
}

long istreamSeek(SDL_RWops *ops, long offset, int loc) {
    auto* stream = static_cast<std::istream*>(ops->hidden.unknown.data1);

    if(loc == SEEK_SET)
        stream->seekg ( offset, std::ios::beg );
    else if(loc == SEEK_CUR)
        stream->seekg ( offset, std::ios::cur );
    else if(loc == SEEK_END)
        stream->seekg ( offset, std::ios::end );

    return stream->fail() ? -1 : (long) stream->tellg();
}

size_t istreamRead(SDL_RWops *ops, void *dat, size_t size, size_t max) {
    if(size == 0)
        return -1;

    auto* stream = static_cast<std::istream *>(ops->hidden.unknown.data1);
    stream->read((char*)dat, size * max);
    return stream->bad() ? -1 : stream->gcount() / size;
}

int istreamClose(SDL_RWops *ops) {
    if(ops)
        SDL_FreeRW(ops);

    return 0;
}
