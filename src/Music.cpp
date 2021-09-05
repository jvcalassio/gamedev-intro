#include <iostream>
#include "../include/Music.hpp"

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
    Open(file);
}

Music::~Music() {
    if(IsOpen()) {
        Stop();
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if(IsOpen()) {
        Mix_PlayMusic(music, times);
    } else {
        std::cout << "sem musica no buffer" << std::endl;
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Mix_LoadMUS(file.c_str());

    if(!IsOpen()) {
        std::cout << "ih deu erro no load music: " << SDL_GetError() << std::endl;
    }
}

bool Music::IsOpen() {
    return (music != nullptr);
}