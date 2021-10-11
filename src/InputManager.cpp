#include "../include/InputManager.hpp"

InputManager& InputManager::GetInstance() {
    static InputManager inst;
    return inst;
}

InputManager::InputManager() {
    for(int i=0;i<6;i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager() {}

void InputManager::Update() {
    SDL_Event evt;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

    while(SDL_PollEvent(&evt)) {
        if(evt.type == SDL_QUIT) {
            quitRequested = true;
        }

        if(evt.type == SDL_MOUSEBUTTONDOWN) {
            mouseState[evt.button.button] = true;
            mouseUpdate[evt.button.button] = updateCounter;
        }

        if(evt.type == SDL_MOUSEBUTTONUP) {
            mouseState[evt.button.button] = false;
            mouseUpdate[evt.button.button] = updateCounter;
        }

        if(evt.type == SDL_KEYDOWN && !evt.key.repeat) {
            keyState[evt.key.keysym.sym] = true;
            keyUpdate[evt.key.keysym.sym] = updateCounter;
        }

        if(evt.type == SDL_KEYUP) {
            keyState[evt.key.keysym.sym] = false;
            keyUpdate[evt.key.keysym.sym] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return (keyState.find(key) != keyState.end() && keyState.at(key) && keyUpdate.at(key) == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return (keyState.find(key) != keyState.end() && !keyState.at(key) && keyUpdate.at(key) == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return (keyState.find(key) != keyState.end() && keyState.at(key) && keyUpdate.at(key) < updateCounter);
}

bool InputManager::MousePress(int button) {
    return (mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return (!mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button) {
    return (mouseState[button] && mouseUpdate[button] < updateCounter);
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

