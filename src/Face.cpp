#include "../include/Face.hpp"
#include "../include/Sound.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

/**
 * Damages the entity by {damage} hitpoints
 * When the entity is dead (0 hp) it's removed
 * and play the associated sound
 * */
void Face::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= 0) {
        Sound* sn = (Sound*) associated.GetComponent("Sound");
        if(sn != nullptr) {
            sn->Play();
            associated.RequestDelete();
        }
    }
}

/**
 * Checks for mouse clicks
 * Damages the entity if clicked
 * */
void Face::Update(float dt) {
    // Sound* sn = (Sound*) associated.GetComponent("Sound");
    // if(IsDead() && sn != nullptr && !sn->IsPlaying()) {
    //     associated.RequestDelete();
    // }
    InputManager& inp = InputManager::GetInstance();
    if(inp.MousePress(LEFT_MOUSE_BUTTON)) {
        if(associated.box.contains(Camera::pos + Vec2((float) inp.GetMouseX(), (float) inp.GetMouseY()))) {
            if(!this->IsDead()) this->Damage(std::rand() % 10 + 10);
        }
    }
}

void Face::Render() {}

bool Face::Is(std::string type) {
    return type == "Face";
}

bool Face::IsDead() {
    return hitpoints <= 0;
}