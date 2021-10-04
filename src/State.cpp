#include <string>
#include "../include/State.hpp"
#include "../include/Face.hpp"
#include "../include/Sound.hpp"
#include "../include/TileMap.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/CameraFollower.hpp"

/**
 * Starts the background image object
 * and loads the background music
 * */
State::State() {
    quitRequested = false;
    GameObject* bgobj = new GameObject();
    bgobj->AddComponent(new Sprite("./assets/img/ocean.jpg", *bgobj));
    bgobj->AddComponent(new CameraFollower(*bgobj)); // makes bg static
    objectArray.emplace_back(bgobj);

    GameObject* tm = new GameObject();
    TileSet* ts = new TileSet(64, 64, "./assets/img/tileset.png");
    tm->AddComponent(new TileMap("./assets/map/tileMap.txt", ts, *tm));
    tm->box.x = 0;
    tm->box.y = 0;
    objectArray.emplace_back(tm);

    music = new Music("./assets/audio/stageState.ogg");
    music->Play();
}

/**
 * Clears the current objects
 * */
State::~State() {
    objectArray.clear();
}

/**
 * Add objects to this state at the {mouseX, mouseY} position
 * */
void State::AddObject(int mouseX, int mouseY) {
    GameObject* enemy = new GameObject();

    Sprite* es = new Sprite("./assets/img/penguinface.png", *enemy);
    // mouseX,Y represents the box center
    enemy->box.x = mouseX - (enemy->box.w / 2);
    enemy->box.y = mouseY - (enemy->box.h / 2);

    enemy->box += Camera::pos;

    Sound* sn = new Sound("./assets/audio/boom.wav", *enemy);

    Face* fc = new Face(*enemy);

    enemy->AddComponent(es);
    enemy->AddComponent(sn);
    enemy->AddComponent(fc);

    objectArray.emplace_back(enemy);
}

void State::LoadAssets() {

}

/**
 * Updates the state
 * Checks if there's any dead entity
 * Runs at every gameloop iteration
 * */
void State::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    quitRequested = inp.QuitRequested() || inp.IsKeyDown(ESCAPE_KEY);
    Camera::Update(dt);

    // new penguin
    if(inp.KeyPress(SPACE_KEY)) {
        Vec2 objPos = Vec2(200, 0).rotated(-M_PI + M_PI*(rand() % 1001)/500.0) + Vec2(inp.GetMouseX(), inp.GetMouseY());
        AddObject((int)objPos.x, (int)objPos.y);
    }

    for(unsigned int i=0;i<objectArray.size();i++) {
        objectArray[i]->Update(dt);
    }

    for(unsigned int i=0;i<objectArray.size();i++) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

/**
 * Renders the current gameobjects
 * */
void State::Render() {
    TileMap* tm = nullptr;
    for(unsigned int i=0;i<objectArray.size();i++) {
        if(objectArray[i]->GetComponent("TileMap") != nullptr) {
            tm = (TileMap*) objectArray[i]->GetComponent("TileMap");
            tm->RenderLayer(0, Camera::pos.x, Camera::pos.y);
        } else {
            objectArray[i]->Render();
        }
    }

    // renders the clouds (or any other level above) above all other sprites
    if(tm != nullptr) {
        for(int i=2;i<=tm->GetDepth();i++) {
            tm->RenderLayer(i-1, Camera::pos.x * i, Camera::pos.y * i);
        }
    }
}

bool State::QuitRequested() {
    return quitRequested;
}