#include <iostream>
#include "../include/Face.hpp"
#include "../include/Sound.hpp"

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

/**
 * Damages the entity by {damage} hitpoints
 * When the entity is dead (0 hp) it's removed from the screen
 * and play some sound
 * */
void Face::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= 0) {
        Sound* sn = (Sound*) associated.GetComponent("Sound");
        if(sn != nullptr && !sn->IsPlaying()) {
            sn->Play();
            associated.RemoveComponent(associated.GetComponent("Sprite"));
        }
        //associated.RequestDelete();
    }
}

/**
 * Checks if the sound is finished.
 * If it is, then the whole GameObject is removed from the state
 * */
void Face::Update(float dt) {
    Sound* sn = (Sound*) associated.GetComponent("Sound");
    if(IsDead() && sn != nullptr && !sn->IsPlaying()) {
        associated.RequestDelete();
    }
}

void Face::Render() {}

bool Face::Is(std::string type) {
    return type == "Face";
}

bool Face::IsDead() {
    return hitpoints <= 0;
}