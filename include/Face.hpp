#ifndef __FACE__
#define __FACE__
#include "Component.hpp"

/**
 * Face represents the properties of some entity
 * Currently, the entities have hitpoints (30 default)
 * Temporary
 * */
class Face : public Component {
    private:
        int hitpoints;

    public:
        Face(GameObject& associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        bool IsDead();
};

#endif