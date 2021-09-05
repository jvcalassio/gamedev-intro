#define INCLUDE_SDL_IMAGE
#include <iostream>
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"

Sprite::Sprite(GameObject& associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(std::string file, GameObject& associated) : Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    if(IsOpen()) SDL_DestroyTexture(texture);
}

/**
 * Loads the {file} image to the texture buffers
 * and sets it's width and height
 * */
void Sprite::Open(std::string file) {
    if(IsOpen()) {
        SDL_DestroyTexture(texture);
    }
    
    Game& game = Game::GetInstance();
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());

    if(!IsOpen()) {
        std::cout << "ih deu erro no load texture: " << SDL_GetError() << std::endl;
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);

    associated.box.w = width;
    associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

/**
 * Renders this sprite on the main renderer
 * */
void Sprite::Render() {
    SDL_Rect dst;
    dst.x = associated.box.x;
    dst.y = associated.box.y;
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

void Sprite::Update(float dt) {

}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}