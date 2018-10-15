//
// Created by cub3d on 11/10/18.
//

#include "PAKFileStream.h"

PAKFileStream::PAKFileStream(PAKFile* file, PAKFileEntry* entry) : entry(entry), read(false) {
    buffer_ = new char[entry->fileSize];
    getFileData(file, entry, buffer_);
}

PAKFileStream::~PAKFileStream() {
    delete[] buffer_;
}

int PAKFileStream::underflow() {
    if(this->gptr() == this->egptr()) {

        printf("T");

        if(!read) {
            // + 0 to indicate that no more bytes were read, will change when file streaming is supported
            this->setg(buffer_, buffer_, buffer_ + entry->fileSize);
            read = true;
        } else {
            this->setg(buffer_, buffer_, buffer_);
        }
    }

    return this->gptr() == this->egptr() ? std::char_traits<char>::eof()
                    : std::char_traits<char>::to_int_type(*this->gptr());
}

PAKFileStream::pos_type PAKFileStream::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode wich) {
    if(dir == std::ios_base::cur) gbump(off);
    return gptr() - eback();
}
