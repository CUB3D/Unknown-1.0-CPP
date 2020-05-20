//
// Created by cub3d on 19/12/18.
//

#ifndef PROJECT_FILE_H
#define PROJECT_FILE_H

#include <memory>
#include <istream>

namespace Unknown {
    class File {
        std::shared_ptr<std::istream> backendStream;

    public:
        File(std::shared_ptr<std::istream> stream);

        std::shared_ptr<std::istream> getStream() const;
        std::string getString() const;

        bool isGood() const;
        virtual explicit operator bool() const;
    };
}

#endif //PROJECT_FILE_H
