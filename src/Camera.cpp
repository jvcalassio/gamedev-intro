#include "../include/Camera.hpp"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

/**
 * Follows target
 * Otherwise, can be moved by keyboard arrows
 * */
void Camera::Update(float dt) {
    if(focus == nullptr) {
        pos = Vec2(0,0);
    } else {
        pos = focus->box.center() - Vec2(512,300);
    }
}