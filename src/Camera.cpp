#include "../include/Camera.hpp"
#include "../include/InputManager.hpp"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

// currently only works when controlled by keyboard arrows
// focus available on T5
void Camera::Update(float dt) {
    if(focus == nullptr) {
        InputManager& inp = InputManager::GetInstance();

        if(inp.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed += Vec2(1,0);
        }
        if(inp.IsKeyDown(LEFT_ARROW_KEY)) {
            speed += Vec2(-1,0);
        }
        if(inp.IsKeyDown(UP_ARROW_KEY)) {
            speed += Vec2(0,-1);
        }
        if(inp.IsKeyDown(DOWN_ARROW_KEY)) {
            speed += Vec2(0,1);
        }

        pos += dt * speed.normalized() * 400;
        speed = Vec2(0,0);
    }
}