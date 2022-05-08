#define INCLUDE_SDL_IMAGE
#include <iostream>
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/Camera.hpp"

Sprite::Sprite(GameObject& associated, int frameCount, float frameTime, 
                float secondsToSelfDestruct) : 
    Component(associated) {
    texture = nullptr;
    scale = Vec2(1,1);
    currentFrame = 0;
    timeElapsed = 0;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->selfDestructCount = Timer();
    this->secondsToSelfDestruct = secondsToSelfDestruct;
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, 
                float frameTime, float secondsToSelfDestruct) : 
    Sprite(associated, frameCount, frameTime, secondsToSelfDestruct) {
    this->Open(file);
}

Sprite::~Sprite() {}

void Sprite::Start() {}

/**
 * Loads the {file} image to the texture buffer
 * and sets it's width and height
 * */
void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

    this->SetClip(0, 0, this->GetWidth(), this->GetHeight());

    associated.box.w = this->GetWidth();
    associated.box.h = this->GetHeight();
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x / this->GetScale().x;
    clipRect.y = y / this->GetScale().y;
    clipRect.w = w / this->GetScale().x;
    clipRect.h = h / this->GetScale().y;
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
    if(this->IsOpen()) {
        SDL_RenderCopyEx(game.GetRenderer(), texture.get(), &clipRect, &dst, 
                         associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}

int Sprite::GetWidth() {
    return (width / frameCount) * scale.x;
}

int Sprite::GetHeight() {
    return height * scale.y;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}

void Sprite::Update(float dt) {
    if(frameCount > 1) {
        timeElapsed += dt;
        if(timeElapsed >= frameTime) {
            this->SetFrame(currentFrame + 1);
            timeElapsed = 0;
        }
    }

    if(secondsToSelfDestruct > 0) {
        selfDestructCount.Update(dt);

        if(selfDestructCount.Get() >= secondsToSelfDestruct) {
            associated.RequestDelete();
        }
    }
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    scale = Vec2(scaleX, scaleY);
    associated.box.w = this->GetWidth();
    associated.box.h = this->GetHeight();
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFrame(int frame) {
    currentFrame = (frame >= frameCount) ? 0 : frame;
    
    this->SetClip(this->GetWidth() * currentFrame, 0, this->GetWidth(), this->GetHeight());
}

void Sprite::SetFrameCount(int frameCount) {
    currentFrame = 0;
    this->frameCount = frameCount;
    this->SetScaleX(this->GetScale().x, this->GetScale().y);
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}