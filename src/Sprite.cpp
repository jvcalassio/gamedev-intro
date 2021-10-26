#define INCLUDE_SDL_IMAGE
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/Camera.hpp"
#include <iostream>

Sprite::Sprite(GameObject& associated) : Component(associated) {
    texture = nullptr;
    scale = Vec2(1,1);
}

Sprite::Sprite(std::string file, GameObject& associated) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Start() {}

/**
 * Loads the {file} image to the texture buffer
 * and sets it's width and height
 * */
void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);

    associated.box.w = width * scale.x;
    associated.box.h = height * scale.y;
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
    this->Render(associated.box.x - Camera::pos.x, 
                 associated.box.y - Camera::pos.y);
}

/**
 * Renders this sprite on the main renderer
 * at position x,y
 * */
void Sprite::Render(float x,  float y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = clipRect.w  * scale.x;
    dst.h = clipRect.h * scale.y;

    Game& game = Game::GetInstance();
    if(IsOpen()) {
        SDL_RenderCopyEx(game.GetRenderer(), texture, &clipRect, &dst, 
                         associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}

int Sprite::GetWidth() {
    return width * scale.x;
}

int Sprite::GetHeight() {
    return height * scale.y;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}

void Sprite::Update(float dt) {}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    scale = Vec2(scaleX, scaleY);
    associated.box.w = width * scaleX;
    associated.box.h = height * scaleY;
}

Vec2 Sprite::GetScale() {
    return scale;
}