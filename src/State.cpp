#include "../include/State.hpp"

State::State() {
    popRequested = false;
    quitRequested = false;
    started = false;
}

State::~State() {
    objectArray.clear();
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
    for(size_t i=0, size=objectArray.size();i<size;i++) {
        if(obj == objectArray[i].get()) {
            wp = objectArray[i];
            return wp;
        }
    }
    return wp;
}

void State::StartArray() {
    for(size_t i=0, size=objectArray.size();i<size;i++) {
        objectArray[i]->Start();
    }
}

/**
 * Updates state's objects
 * */
void State::UpdateArray(float dt) {
    for(size_t i=0, size=objectArray.size();i<size;i++) {
        objectArray[i]->Update(dt);
    }
}

/**
 * Renders state's objects
 * */
void State::RenderArray() {
    for(size_t i=0, size=objectArray.size();i<size;i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

bool State::PopRequested() {
    return popRequested;
}
