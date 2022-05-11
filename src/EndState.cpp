#include "../include/EndState.hpp"
#include "../include/GameData.hpp"
#include "../include/Sprite.hpp"
#include "../include/Text.hpp"
#include "../include/InputManager.hpp"
#include "../include/TitleState.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"

EndState::EndState() : State() {}

EndState::~EndState() {
    backgroundMusic->Stop();
}

void EndState::LoadAssets() {
    GameObject* bg = new GameObject();
    GameObject* text = new GameObject();
    SDL_Color color;
    if(GameData::playerVictory) {
        bg->AddComponent(new Sprite(*bg, "./assets/img/win.jpg"));
        this->backgroundMusic = new Music("./assets/audio/endStateWin.ogg");
        color = {0, 0, 0, 0};
        text->box.y = 500;
    } else {
        bg->AddComponent(new Sprite(*bg, "./assets/img/lose.jpg"));
        this->backgroundMusic = new Music("./assets/audio/endStateLose.ogg");
        color = {255, 255, 255, 0};
        text->box.y = 550;
    }
    this->AddObject(bg);

    text->box.x = 136;
    text->AddComponent(new Text(*text, "./assets/font/Call me maybe.ttf", 30, Text::TextStyle::BLENDED,
                        "Pressione ESPACO para jogar novamente ou ESC para sair", color, true));
    this->AddObject(text);
}

void EndState::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    quitRequested = inp.QuitRequested() || inp.KeyPress(ESCAPE_KEY);

    this->UpdateArray(dt);

    if(inp.KeyPress(SPACE_KEY)) {
        this->Pause();
        popRequested = true;
    }

    if(popRequested || quitRequested) {
        backgroundMusic->Stop();
    }
}

void EndState::Render() {
    this->RenderArray();
}

void EndState::Start() {
    this->LoadAssets();

    this->StartArray();

    started = true;
    backgroundMusic->Play();
}

void EndState::Pause() {
    backgroundMusic->Stop();
}

void EndState::Resume() {
    Camera::Unfollow();
    Camera::Update(0);
    backgroundMusic->Play();
}
