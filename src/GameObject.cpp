#include "../include/GameObject.hpp"

GameObject::GameObject() : box(Rect()) {
    isDead = false;
    started = false;
    angleDeg = 0;
}

GameObject::~GameObject() {
    components.clear();
}

/**
 * Starts all this object's components
 * */
void GameObject::Start() {
    for(size_t i=0, size=components.size();i<size;i++) {
        components[i]->Start();
    }
    started = true;
}

/**
 * Updates all this object's components
 * */
void GameObject::Update(float dt) {
    for(size_t i=0, size=components.size();i<size;i++) {
        components[i]->Update(dt);
    }
}

/**
 * Renders all this object's components
 * (if render is implemented)
 * */
void GameObject::Render() {
    for(size_t i=0, size=components.size();i<size;i++) {
        components[i]->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

/**
 * Kills this object
 * */
void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
    if(started) cpt->Start();
}

void GameObject::RemoveComponent(Component* cpt) {
    for(size_t i=0, size=components.size();i<size;i++) {
        if(components[i].get() == cpt) {
            components.erase(components.begin() + i);
        }
    }
}

/**
 * Get this object's first component of {type} type
 * */
Component* GameObject::GetComponent(std::string type) {
    for(size_t i=0, size=components.size();i<size;i++) {
        if(components[i]->Is(type)) return components[i].get();
    }
    return nullptr;
}

/**
 * Notify all it's Components about the collision
 * @param other The collided GameObject
 */
void GameObject::NotifyCollision(GameObject& other) {
    for(size_t i=0, size=components.size();i<size;i++) {
        components[i]->NotifyCollision(other);
    }
}