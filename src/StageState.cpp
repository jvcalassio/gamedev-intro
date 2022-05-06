#include <string>
#include "../include/StageState.hpp"
#include "../include/Sound.hpp"
#include "../include/TileMap.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/CameraFollower.hpp"
#include "../include/Alien.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/Collider.hpp"
#include "../include/Collision.hpp"
#include <iostream>

/**
 * Starts the background image object, tilemap,
 * first alien and loads the background music
 * */
StageState::StageState() : State() {
    // adds background to the game screen
    GameObject* bgobj = new GameObject();
    bgobj->AddComponent(new Sprite(*bgobj, "./assets/img/ocean.jpg"));
    bgobj->AddComponent(new CameraFollower(*bgobj)); // makes bg static
    this->AddObject(bgobj);

    // adds tilemap to the game screen
    GameObject* tm = new GameObject();
    TileSet* ts = new TileSet(64, 64, "./assets/img/tileset.png");
    tm->AddComponent(new TileMap(*tm, "./assets/map/tileMap.txt", ts));
    tm->box.x = 0;
    tm->box.y = 0;
    this->AddObject(tm);

    // adds the first alien to the game (temporary)
    GameObject* alien = new GameObject();
    alien->AddComponent(new Alien(*alien, 6));
    alien->box.set_center(Vec2(512,300));
    this->AddObject(alien);

    // adds the penguin to the game screen
    GameObject* penguin = new GameObject();
    penguin->AddComponent(new PenguinBody(*penguin));
    penguin->box.set_center(Vec2(704,640));
    Camera::Follow(penguin);
    this->AddObject(penguin);

    backgroundMusic = new Music("./assets/audio/stageState.ogg");
    //backgroundMusic->Play();
}

/**
 * Clears the current objects
 * */
StageState::~StageState() {
    
}

/**
 * Starts state's objects
 * */
void StageState::Start() {
    this->LoadAssets();

    this->StartArray();

    started = true;
}

void StageState::LoadAssets() {}

/**
 * Updates the state
 * Checks if there's any dead entity, and input events
 * 
 * Runs at every gameloop iteration
 * */
void StageState::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    quitRequested = inp.QuitRequested() || inp.IsKeyDown(ESCAPE_KEY);
    Camera::Update(dt);

    this->UpdateArray(dt);

    for(size_t i=0, size=objectArray.size();i<size;i++) {
        Collider* collider = (Collider*) objectArray[i]->GetComponent("Collider");
        if(objectArray[i].get() && collider != nullptr) {
            // all the elements before this one were tested already
            // checks for collisions on all subsequent elements
            for(size_t j=i+1, sizej=objectArray.size();j<sizej;j++) {
                Collider* colliderj = (Collider*) objectArray[j]->GetComponent("Collider");
                if(objectArray[j].get() && colliderj != nullptr) {
                    bool body = objectArray[i]->GetComponent("PenguinBody") || objectArray[j]->GetComponent("PenguinBody");
                    bool cannon = objectArray[i]->GetComponent("PenguinCannon") || objectArray[j]->GetComponent("PenguinCannon");
                    if(!(body && cannon)) {
                        bool isColliding = Collision::IsColliding(
                            collider->box, 
                            colliderj->box, 
                            objectArray[i]->angleDeg * (M_PI/180), 
                            objectArray[j]->angleDeg * (M_PI/180)
                        );

                        if(isColliding) {
                            objectArray[i]->NotifyCollision(*objectArray[j].get());
                            objectArray[j]->NotifyCollision(*objectArray[i].get());
                        }
                    }
                }
            }
        }
    }

    for(size_t i=0, size=objectArray.size();i<size;i++) {
        if(objectArray[i].get() && objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

/**
 * Renders the current gameobjects
 * 
 * Layers 2+ of the tilemap are rendered above other objects
 * */
void StageState::Render() {
    TileMap* tm = nullptr;
    for(size_t i=0, size=objectArray.size();i<size;i++) {
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

bool StageState::QuitRequested() {
    return quitRequested;
}

void StageState::Pause() {}
void StageState::Resume() {}