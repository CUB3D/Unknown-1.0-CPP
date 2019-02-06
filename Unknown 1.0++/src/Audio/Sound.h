//
// Created by cub3d on 14/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SOUND_H
#define UNKNOWN_DEVELOPMENT_TOOL_SOUND_H

#include <SDL_mixer.h>

namespace Unknown
{
    class Sound
    {
        int channel = -1;

    protected:
        Mix_Chunk *chunk;
    public:
        Sound(Mix_Chunk *chunk);

        void play(int loops);
        void playSingle();
        bool isPlaying() const;

        virtual void init();


        virtual ~Sound();
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_SOUND_H
