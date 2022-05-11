#ifndef __PENGUIN_BODY__
#define __PENGUIN_BODY__
#define PENGUIN_HP 100
#define PENGUIN_MAX_SPEED 500
#define PENGUIN_ACCELERATION 10
#include <string>
#include <memory>
#include "Component.hpp"
#include "Vec2.hpp"

/**
 * Player penguin (body)
 * 
 * Handles player keyboard inputs, moves
 */
class PenguinBody : public Component {
    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;

        void Kill();

    public:
        static PenguinBody* player;

        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision(GameObject& other);
        Vec2 GetPosition();
};

#endif