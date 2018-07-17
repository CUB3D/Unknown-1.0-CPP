//
// Created by cub3d on 15/07/2018.
//

#include "WAVSound.h"
#include <SDL_mixer.h>

Unknown::WAVSound::WAVSound(const std::string& str) : str(str), Sound(nullptr) {

}

void Unknown::WAVSound::init() {
    this->chunk = Mix_LoadWAV(str.c_str());
}
