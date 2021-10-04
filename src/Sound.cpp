#include "../include/Sound.hpp"
#include "../include/Resources.hpp"

Sound::Sound(GameObject& associated) : Component(associated) {
    chunk = nullptr;
}

Sound::Sound(std::string file, GameObject& associated) : Sound(associated) {
    Open(file);
}

Sound::~Sound() {}

void Sound::Play(int times) {
    if(IsOpen()) channel = Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop() {
    if(IsOpen()) Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
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