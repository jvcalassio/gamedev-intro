#include <iostream>
#include "../include/Resources.hpp"
#include "../include/Game.hpp"

// makes sure that the static props are initialized
std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

/**
 * Loads image from {file} if it isn't loaded yet
 * Otherwise, returns pointer to the existing texture corresponding to {file}
 * */
std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
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

    std::shared_ptr<SDL_Texture> sp(texture, [](SDL_Texture* t){
        SDL_DestroyTexture(t);
    });
    Resources::imageTable.emplace(file, sp);
    return sp;
}

void Resources::ClearImages() {
    for(auto& i : Resources::imageTable) {
        if(i.second.unique()) {
            imageTable.erase(i.first);
        }
    }
    // handle SIGTRAP nostop noprint noignore
    // for(auto it = Resources::imageTable.begin(); it != Resources::imageTable.end(); it++) {
    //     if(it->second.unique()) {
    //         //SDL_DestroyTexture(it->second.get());
    //         Resources::imageTable.erase(it->first);
    //     }
    // }
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
    Resources::musicTable.clear();
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
    Resources::soundTable.clear();
}

TTF_Font* Resources::GetFont(std::string file, int size) {
    std::string strfile = file + std::to_string(size);

    auto res = Resources::fontTable.find(strfile);
    if(res != Resources::fontTable.end()) {
        return res->second;
    }

    TTF_Font* font = TTF_OpenFont(file.c_str(), size);

    if(font == nullptr) {
        std::cout << "ih deu erro no open font: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    Resources::fontTable.emplace(strfile, font);
    return font;
}

void Resources::ClearFonts() {
    for(auto& i : Resources::fontTable) {
        TTF_CloseFont(i.second);
    }
    Resources::fontTable.clear();
}
