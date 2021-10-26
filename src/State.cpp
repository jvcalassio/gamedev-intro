#include <string>
#include "../include/State.hpp"
#include "../include/Sound.hpp"
#include "../include/TileMap.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/CameraFollower.hpp"
#include "../include/Alien.hpp"

/**
 * Starts the background image object, tilemap,
 * first alien and loads the background music
 * */
State::State() {
    quitRequested = false;
    started = false;

    GameObject* bgobj = new GameObject();
    bgobj->AddComponent(new Sprite("./assets/img/ocean.jpg", *bgobj));
    bgobj->AddComponent(new CameraFollower(*bgobj)); // makes bg static
    this->AddObject(bgobj);

    GameObject* tm = new GameObject();
    TileSet* ts = new TileSet(64, 64, "./assets/img/tileset.png");
    tm->AddComponent(new TileMap("./assets/map/tileMap.txt", ts, *tm));
    tm->box.x = 0;
    tm->box.y = 0;
    this->AddObject(tm);

    GameObject* alien = new GameObject();
    alien->AddComponent(new Alien(*alien, 6));
    alien->box.set_center(Vec2(512,300));
    //Camera::Follow(alien);
    this->AddObject(alien);

    music = new Music("./assets/audio/stageState.ogg");
    //music->Play();
}

/**
 * Clears the current objects
 * */
State::~State() {
    objectArray.clear();
}

/**
 * Starts state's objects
 * */
void State::Start() {
    this->LoadAssets();

    for(auto& obj : objectArray) {
        obj->Start();
    }

    started = true;
}

/**
 * Adds objects to objArray
 * and starts them if the state is already started
 * */
std::weak_ptr<GameObject> State::AddObject(GameObject* obj) {
    std::shared_ptr<GameObject> sp(obj);
    objectArray.push_back(sp);

    if(started) sp->Start();

    std::weak_ptr<GameObject> wp = sp;
    return wp;
}

/**
 * Returns weak_ptr for providaded default pointer
 * */
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* obj) {
    std::weak_ptr<GameObject> wp;
    for(auto& i : objectArray) {
        if(obj == i.get()) {
            wp = i;
            return wp;
        }
    }
    return wp;
}

void State::LoadAssets() {

}

/**
 * Updates the state
 * Checks if there's any dead entity, and input events
 * 
 * Runs at every gameloop iteration
 * */
void State::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    quitRequested = inp.QuitRequested() || inp.IsKeyDown(ESCAPE_KEY);
    Camera::Update(dt);

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
 * 
 * Layers 2+ of the tilemap are rendered above other objects
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