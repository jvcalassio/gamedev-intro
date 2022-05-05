#ifndef __BULLET__
#define __BULLET__
#include <string>
#include "Component.hpp"
#include "Vec2.hpp"

/**
 * Alien Minion projectile
 * 
 * Supports both types of projectiles
 * */
class Bullet : public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;

    public:
        bool targetsPlayer;
        
        Bullet(GameObject& associated, float angle, float speed, int damage, 
            float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
        void NotifyCollision(GameObject& other);
};

#endif