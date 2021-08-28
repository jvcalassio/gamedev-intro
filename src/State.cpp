#include "../include/State.hpp"
#include <iostream>

State::State() {
    quitRequested = false;
    // bg = Sprite(std::string("teste.png"));
    // https://stackoverflow.com/questions/2722879/calling-constructors-in-c-without-new
    bg = new Sprite("./assets/img/ocean.jpg");
    music = new Music("./assets/audio/stageState.ogg");
    music->Play();
}

void State::LoadAssets() {

}

void State::Update(float dt) {
    if(SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg->Render(0,0);
}

bool State::QuitRequested() {
    return quitRequested;
}