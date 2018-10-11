//
// Created by cub3d on 10/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_FILESYSTEM_H
#define UNKNOWN_DEVELOPMENT_TOOL_FILESYSTEM_H

#include <string>
#include <boost/shared_ptr.hpp>

namespace Unknown
{
    class Filesystem
    {
    private:
        Filesystem() = default;

    public:
        void mount(const std::string& path);
        void alias(const std::string& src, const std::string& dest);

        bool exists(const std::string& str);

        static std::shared_ptr<std::istream> readFile(const std::string &path);
        static Filesystem& getFS();
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_FILESYSTEM_H
