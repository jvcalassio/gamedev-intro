#ifndef __PENGUIN_CANNON__
#define __PENGUIN_CANNON__
#define PENGUIN_BULLET_SPEED 700
#define PENGUIN_BULLET_DAMAGE 20
#define PENGUIN_BULLET_DISTANCE 2000
#define PENGUIN_BULLET_COOLDOWN 1
#include <string>
#include <memory>
#include "Component.hpp"
#include "Timer.hpp"

/**
 * Player penguin (cannon)
 * 
 * Handles player mouse input, shoots
 */
class PenguinCannon : public Component {
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer bulletCooldown;

    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> pbody);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();
        void NotifyCollision(GameObject& other);
};

#endif