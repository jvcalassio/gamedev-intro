#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed,
                int damage, float maxDistance, std::string sprite) : Component(associated) {
    Sprite* sp = new Sprite(sprite, associated);
    associated.angleDeg = angle * (180/M_PI);
    associated.AddComponent(sp);

    distanceLeft = maxDistance;
    this->speed = Vec2(1, 0).rotated(angle) * speed;
    this->damage = damage;
}

void Bullet::Start() {}

/**
 * Moves bullet with constant speed
 * or deletes if reached max distance
 * */
void Bullet::Update(float dt) {
    Vec2 mov = speed * dt;
    associated.box += mov;
    distanceLeft -= mov.magnitude();
    if(distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
    return (type == "Bullet");
}

int Bullet::GetDamage() {
    return damage;
}