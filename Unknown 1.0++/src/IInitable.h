//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_IINITABLE_H
#define UNKNOWN_DEVELOPMENT_TOOL_IINITABLE_H

namespace Unknown
{
    template<typename... initArgs>
    class IInitable
    {
    public:
        virtual void init(initArgs... args) = 0;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_IINITABLE_H
