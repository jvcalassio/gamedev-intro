#include "../include/GameObject.hpp"

GameObject::GameObject() : box(Rect()) {
    isDead = false;
}

GameObject::~GameObject() {
    components.clear();
}

/**
 * Updates all this object's components
 * */
void GameObject::Update(float dt) {
    for(auto& c : components) {
        c->Update(dt);
    }
}

/**
 * Renders all this object's components
 * (if render is implemented)
 * */
void GameObject::Render() {
    for(auto& c : components) {
        c->Render();
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
}

void GameObject::RemoveComponent(Component* cpt) {
    for(int i=0;i<components.size();i++) {
        if(components[i].get() == cpt) {
            components.erase(components.begin() + i);
        }
    }
}

/**
 * Get this object's first component of {type} type
 * */
Component* GameObject::GetComponent(std::string type) {
    for(auto& c : components) {
        if(c->Is(type)) return c.get();
    }
    return nullptr;
}