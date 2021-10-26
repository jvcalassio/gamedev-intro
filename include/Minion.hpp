#ifndef __MINION__
#define __MINION__
#define DEFAULT_BULLET_SPEED 400
#define DEFAULT_BULLET_DAMAGE 50
#define DEFAULT_BULLET_DISTANCE 2000
#define MINION_DISTANCE 160
#define MINION_SPEED 0.25
#include <string>
#include <memory>
#include "Component.hpp"
#include "Vec2.hpp"

/**
 * Alien Minion
 * 
 * Single instance of the alien's minions
 * Shoots single bullets
 * */
class Minion : public Component {
    private:
        std::weak_ptr<GameObject> alienCenter;
        float arc;

    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg);
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
};

#endif