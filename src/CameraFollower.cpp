#include "../include/CameraFollower.hpp"
#include "../include/Camera.hpp"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Start() {}

void CameraFollower::Render() {}

bool CameraFollower::Is(std::string type) {
    return (type == "CameraFollower");
}