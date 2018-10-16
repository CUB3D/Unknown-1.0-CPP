//
// Created by cub3d on 11/10/18.
//

#include "PAKFileStream.h"

PAKFileStream::PAKFileStream(PAKFile* file, PAKFileEntry* entry) : entry(entry), read(false) {
    buffer_ = new char[entry->fileSize];
    getFileData(file, entry, buffer_);
    setg(buffer_, buffer_, buffer_ + entry->fileSize);
}

//PAKFileStream::~PAKFileStream() {
//    delete[] buffer_;
//}
//
//int PAKFileStream::underflow() {
//    if(this->gptr() == this->egptr()) {
//        printf("Underflowing\n");
//        if(!read) {
//            // + 0 to indicate that no more bytes were read, will change when file streaming is supported
//            this->setg(buffer_, buffer_, buffer_ + entry->fileSize);
//            read = true;
//        } else {
//            this->setg(buffer_, buffer_, buffer_);
//        }
//    }
//
//    return this->gptr() == this->egptr() ? std::char_traits<char>::eof()
//                    : std::char_traits<char>::to_int_type(*this->gptr());
//}
//
PAKFileStream::pos_type PAKFileStream::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode wich) {
    printf("Seek dir: %d, Offset: %d, mode: %d\n", dir, off, wich);

    if (dir == std::ios_base::cur)
        gbump(off);
    else if (dir == std::ios_base::end)
        setg(eback(), egptr() + off, egptr());
    else if (dir == std::ios_base::beg)
        setg(eback(), eback() + off, egptr());
    return gptr() - eback();
}

std::fpos<mbstate_t> PAKFileStream::seekpos(pos_type sp, std::ios_base::openmode which) {
    printf("Seekpos sp: %d, mode: %d\n", sp, which);
    return seekoff(off_type(sp), std::ios_base::beg, which);
}
