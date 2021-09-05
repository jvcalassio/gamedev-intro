#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__
#include <vector>
#include <string>
#include <memory>
#include "Component.hpp"
#include "Rect.hpp"

// Avoids circular dependencies
class Component;

/**
 * Game Objects
 * Represents entities on the screen
 * It may contain multiple sprites, sounds, faces, or any Component
 * */
class GameObject {
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;

    public:
        Rect box;

        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
};

#endif