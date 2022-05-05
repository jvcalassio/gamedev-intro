#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"
#include "../include/Collider.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, 
            float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer) : 
    Component(associated) {
    Sprite* sp = new Sprite(associated, sprite, frameCount, frameTime);
    Collider* cl = new Collider(associated);
    associated.angleDeg = angle * (180/M_PI);
    associated.AddComponent(sp);
    associated.AddComponent(cl);

    distanceLeft = maxDistance;
    this->speed = Vec2(1, 0).rotated(angle) * speed;
    this->damage = damage;
    this->targetsPlayer = targetsPlayer;
}

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

/**
 * Handles any collision
 * 
 * @param other The collided GameObject 
 */
void Bullet::NotifyCollision(GameObject& other) {
    bool penguin = other.GetComponent("PenguinBody") || other.GetComponent("PenguinCannon");
    if(other.GetComponent("Alien") && !targetsPlayer) {
        distanceLeft = 0;
        associated.RequestDelete();
    } else if(penguin && targetsPlayer) {
        distanceLeft = 0;
        associated.RequestDelete();
    }
}