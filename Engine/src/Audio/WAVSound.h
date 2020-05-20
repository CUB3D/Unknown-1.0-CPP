//
// Created by cub3d on 15/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_WAVSOUND_H
#define UNKNOWN_DEVELOPMENT_TOOL_WAVSOUND_H

#include "Sound.h"
#include <string>

namespace Unknown
{
    class WAVSound : public Sound
    {
        const std::string str;
    public:
        WAVSound(const std::string& str);

        virtual void init() override;

    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_WAVSOUND_H
