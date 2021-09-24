#include "../include/Resources.hpp"
#include "../include/Game.hpp"
#include <iostream>

// makes sure that the static props are initialized
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

/**
 * Loads image from {file} if it isn't loaded yet
 * Otherwise, returns pointer to the existing texture corresponding to {file}
 * */
SDL_Texture* Resources::GetImage(std::string file) {
    auto res = Resources::imageTable.find(file);
    if(res != Resources::imageTable.end()) {
        return res->second;
    }

    Game& game = Game::GetInstance();
    SDL_Texture* texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());

    if(texture == nullptr) {
        std::cout << "ih deu erro no load texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    Resources::imageTable.emplace(file, texture);
    return texture;
}

void Resources::ClearImages() {
    for(auto& i : Resources::imageTable) {
        SDL_DestroyTexture(i.second);
    }
    Resources::imageTable.clear();
}

/**
 * Loads music from {file} if it isn't loaded yet
 * Otherwise, returns pointer to the existing music corresponding to {file}
 * */
Mix_Music* Resources::GetMusic(std::string file) {
    auto res = Resources::musicTable.find(file);
    if(res != Resources::musicTable.end()) {
        return res->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if(music == nullptr) {
        std::cout << "ih deu erro no load music: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    Resources::musicTable.emplace(file, music);
    return music;
}

void Resources::ClearMusics() {
    for(auto& i : Resources::musicTable) {
        Mix_FreeMusic(i.second);
    }
}

/**
 * Loads sound from {file} if it isn't loaded yet
 * Otherwise, returns pointer to the existing sound corresponding to {file}
 * */
Mix_Chunk* Resources::GetSound(std::string file) {
    auto res = Resources::soundTable.find(file);
    if(res != Resources::soundTable.end()) {
        return res->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());

    if(chunk == nullptr) {
        std::cout << "ih deu erro no load sound: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    Resources::soundTable.emplace(file, chunk);
    return chunk;
}

void Resources::ClearSounds() {
    for(auto& i : Resources::soundTable) {
        Mix_FreeChunk(i.second);
    }
}