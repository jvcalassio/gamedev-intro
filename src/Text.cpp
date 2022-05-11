#include <string>
#include <iostream>
#include "../include/Camera.hpp"
#include "../include/Game.hpp"
#include "../include/GameObject.hpp"
#include "../include/Resources.hpp"
#include "../include/Text.hpp"

Text::Text(GameObject& associated, std::string fontFile, 
            int fontSize, TextStyle style, std::string text, 
            SDL_Color color, bool blink) : 
    Component(associated) {
    font = Resources::GetFont(fontFile, fontSize);
    texture = nullptr;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    this->blink = blink;
    blinkFlag = false;
    this->RemakeTexture();
}

Text::~Text() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::RemakeTexture() {
    if(texture != nullptr)
        SDL_DestroyTexture(texture);

    SDL_Surface* surface;
    switch(style) {
        case (Text::TextStyle::SOLID):
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
        case (Text::TextStyle::SHADED):
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0, 0, 0, 0});
            break;
        case (Text::TextStyle::BLENDED):
            surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
    }

    Game& gm = Game::GetInstance();
    texture = SDL_CreateTextureFromSurface(gm.GetRenderer(), surface);
    
    if(texture == nullptr) {
        std::cout << "erro ao carregar textura : " << SDL_GetError() << std::endl;
        return;
    }
    
    associated.box.w = surface->w;
    associated.box.h = surface->h;
    SDL_FreeSurface(surface);
}

void Text::Update(float dt) {
    if(!blink) return;

    if(blinkTimer.Get() >= BLINK_TIME) {
        blinkFlag = !blinkFlag;

        blinkTimer.Restart();
    } else {
        blinkTimer.Update(dt);
    }
}

void Text::Render() {
    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = associated.box.w;
    clipRect.h = associated.box.h;

    SDL_Rect dst;
    dst.x = associated.box.x - Camera::pos.x;
    dst.y = associated.box.y - Camera::pos.y;
    dst.w = associated.box.w;
    dst.h = associated.box.h;

    Game& game = Game::GetInstance();
    if(texture != nullptr && !blinkFlag) {
        SDL_RenderCopyEx(game.GetRenderer(), texture, &clipRect, &dst,
                         associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}

bool Text::Is(std::string type) {
    return type == "Text";
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
    this->RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    this->RemakeTexture();
}

void Text::SetStyle(Text::TextStyle style) {
    this->style = style;
    this->RemakeTexture();
}

void Text::SetText(std::string text) {
    this->text = text;
    this->RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    this->RemakeTexture();
}
