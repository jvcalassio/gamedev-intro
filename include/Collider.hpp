#ifndef __COLLIDER__
#define __COLLIDER__
#include <string>
#include "Component.hpp"
#include "Vec2.hpp"
#include "Rect.hpp"
#ifdef DEBUG
#include "Camera.hpp"
#include "Game.hpp"
#define INCLUDE_SDL
#include "SDL_include.hpp"
#endif // DEBUG

class Collider : public Component {
    private:
        Vec2 scale;
        Vec2 offset;

    public:
        Rect box;

        Collider(GameObject& associated, Vec2 scale = Vec2(1,1), Vec2 offset = Vec2(0,0));
        void Update(float dt);
        void Render();
        void Start();
        bool Is(std::string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
};

#endif