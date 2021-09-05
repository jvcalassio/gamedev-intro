#include <iostream>
#include "../include/Sound.hpp"

Sound::Sound(GameObject& associated) : Component(associated) {
    chunk = nullptr;
}

Sound::Sound(std::string file, GameObject& associated) : Sound(associated) {
    Open(file);
}

Sound::~Sound() {
    if(IsOpen()) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }   
}

void Sound::Play(int times) {
    if(IsOpen()) channel = Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop() {
    if(IsOpen()) Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
    chunk = Mix_LoadWAV(file.c_str());
    if(!IsOpen()) {
        std::cout << "ih deu erro ao carregar o sound: " << SDL_GetError() << std::endl;
    }
}

bool Sound::IsOpen() {
    return (chunk != nullptr);
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(std::string type) {
    return type == "Sound";
}

bool Sound::IsPlaying() {
    if(IsOpen() && channel >= 0 && channel <= 32) return Mix_Playing(channel);
    return false;
}