#ifndef __CAMERA__
#define __CAMERA__
#include "GameObject.hpp"
#include "Vec2.hpp"

/**
 * Game Camera
 * */
class Camera {
    private:
        static GameObject* focus;

    public:
        static Vec2 pos;
        static Vec2 speed;

        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);
};

#endif