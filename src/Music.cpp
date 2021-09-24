#include <iostream>
#include "../include/Music.hpp"
#include "../include/Resources.hpp"

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) : Music() {
    Open(file);
}

Music::~Music() {
    if(IsOpen()) Stop();
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
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
    return (music != nullptr);
}