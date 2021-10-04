#ifndef __CAMERA_FOLLOWER__
#define __CAMERA_FOLLOWER__
#include <string>
#include "Component.hpp"

/**
 * Makes given GameObject static on screen
 * It's necessary since all sprites follow the camera by default
 * */
class CameraFollower : public Component {
    public:
        CameraFollower(GameObject& go);
        void Update(float dt);
        void Render();
        bool Is(std::string type);   
};

#endif