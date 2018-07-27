//
// Created by cub3d on 14/07/2018.
//

#include "Sound.h"
#include <cstdio>

Unknown::Sound::Sound(Mix_Chunk* chunk) : chunk(chunk) {
}

void Unknown::Sound::play(int loops)  {
    if(this->chunk == nullptr) {
        this->init();
    }

    this->channel = Mix_PlayChannel(-1, this->chunk, loops - 1);
    if(this->channel == -1) {
        printf("Unable to play audio: %s\n", Mix_GetError());
    }
}

void Unknown::Sound::playSingle()  {
    this->play(0);
}

Unknown::Sound::~Sound() {
    Mix_FreeChunk(this->chunk);
    this->channel = -1;
}

bool Unknown::Sound::isPlaying() const {
    return Mix_Playing(this->channel);
}

void Unknown::Sound::init() {
}
