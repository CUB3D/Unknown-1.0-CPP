//
// Created by cub3d on 17/05/2020.
//

#include "SDLAudioEngine.h"
#include <SDL_mixer.h>
#include <SDL.h>

void SDLAudioEngine::init() {
    if(SDL_Init(SDL_INIT_AUDIO) == -1) {
        printf("Error: SDL failed to initialise audio handling, %s\n", Mix_GetError());
//        quit(ErrorCodes::SDL_MIXER_INIT_FAIL);
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Failed to setup audio mixer %s\n", Mix_GetError());
//        quit(ErrorCodes::SDL_MIXER_OPEN_AUDIO_FAIL);
    }

    Mix_AllocateChannels(64);
}

void SDLAudioEngine::shutdown() {
    Mix_CloseAudio();
}
