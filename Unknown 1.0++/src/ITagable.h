//
// Created by cub3d on 31/07/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ITAGABLE_H
#define UNKNOWN_DEVELOPMENT_TOOL_ITAGABLE_H

#include <string>

class ITagable
{
public:
    virtual const std::string getTag() const = 0;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_ITAGABLE_H
