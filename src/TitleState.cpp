#include "../include/TitleState.hpp"
#include "../include/Game.hpp"
#include "../include/Sprite.hpp"
#include "../include/Text.hpp"
#include "../include/GameObject.hpp"
#include "../include/InputManager.hpp"
#include "../include/StageState.hpp"
#include "../include/Camera.hpp"

TitleState::TitleState() : State() {}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {
    GameObject* bgobj = new GameObject();
    bgobj->AddComponent(new Sprite(*bgobj, "./assets/img/title.jpg"));
    this->AddObject(bgobj);

    GameObject* text = new GameObject();
    text->box.x = 321;
    text->box.y = 500;
    text->AddComponent(new Text(*text, "./assets/font/Call me maybe.ttf", 30, Text::TextStyle::BLENDED,
                        "Pressione ESPACO para iniciar", {0, 0, 0, 0}, true));
    this->AddObject(text);
}

void TitleState::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    quitRequested = inp.QuitRequested() || inp.KeyPress(ESCAPE_KEY);

    if(quitRequested) return;

    this->UpdateArray(dt);

    if(inp.IsKeyDown(SPACE_KEY)) {
        StageState* stage = new StageState();
        Game& gm = Game::GetInstance();
        gm.Push(stage);
    }
}

void TitleState::Render() {
    this->RenderArray();
}

void TitleState::Start() {
    this->LoadAssets();
    this->StartArray();
    started = true;
}

void TitleState::Pause() {}

void TitleState::Resume() {
    Camera::Unfollow();
    Camera::Update(0);
}
