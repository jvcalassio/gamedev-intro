#ifndef __ALIEN__
#define __ALIEN__
#define ALIEN_HP 50
#define ALIEN_SPIN 0.25
#define ALIEN_SPEED 250
#include <string>
#include <queue>
#include <vector>
#include <memory>
#include "Component.hpp"
#include "Vec2.hpp"

/**
 * Alien enemy
 * 
 * Currently controlled by the player, moves and shoots
 * with it's minions
 * */
class Alien : public Component {
    private:
        /**
         * Alien action definition
         * */
        class Action {
            public:
                enum ActionType {MOVE, SHOOT};

                ActionType type;
                Vec2 pos;

                Action(ActionType action, float x, float y);
        };

        Vec2 speed;
        int hp;
        int nMinions;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;

    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif