#ifndef __COMPONENT__
#define __COMPONENT__
#include <string>
#include "GameObject.hpp"

// Avoids circular dependencies
class GameObject;

/**
 * Game Object component
 * Interface for game object's components
 * Used by Sprite, Sound and Face
 * */
class Component {
    protected:
        GameObject& associated;

    public:
        explicit Component(GameObject& associated);
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;
};

#endif