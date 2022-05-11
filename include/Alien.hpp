#ifndef __ALIEN__
#define __ALIEN__
#define ALIEN_HP 200
#define ALIEN_SPIN 0.25
#define ALIEN_SPEED 100
#define ALIEN_REST_TIME 1.5
#include <string>
#include <queue>
#include <vector>
#include <memory>
#include "Component.hpp"
#include "Vec2.hpp"
#include "Timer.hpp"

/**
 * Alien enemy
 * 
 * Controlled by a FSM, follows the penguins
 * */
class Alien : public Component {
    private:
        enum AlienState { MOVING, RESTING };

        int hp;
        int nMinions;
        AlienState state;
        Timer restTimer;
        Vec2 destination;
        Vec2 speed;
        std::vector<std::weak_ptr<GameObject>> minionArray;

        void Kill();

    public:
        static int alienCount;

        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision(GameObject& other);
};

#endif