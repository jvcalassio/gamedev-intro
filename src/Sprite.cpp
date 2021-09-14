#include <iostream>
#define INCLUDE_SDL_IMAGE
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(std::string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    if(IsOpen()) SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
    if(IsOpen()) {
        SDL_DestroyTexture(texture);
    }
    
    Game& game = Game::GetInstance();
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());

    if(!IsOpen()) {
        std::cout << "ih deu erro no load texture" << std::endl;
        exit(0);
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = clipRect.w;
    dst.h = clipRect.h;

    Game& game = Game::GetInstance();
    if(IsOpen()) {
        SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dst);
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}