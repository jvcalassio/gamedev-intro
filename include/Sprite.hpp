#ifndef __SPRITE__
#define __SPRITE__
#define INCLUDE_SDL
#include <string>
#include "SDL_include.h"
#include "Component.hpp"

/**
 * Sprite 
 * Manages SDL2 functions for image handling (load, clip, render)
 * 
 * Implemented as a Component since it's meant to be used as an
 * element of GameObject
 * */
class Sprite : public Component {
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;

    public:
        Sprite(GameObject& associated);
        explicit Sprite(std::string file, GameObject& associated);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(std::string type);
};

#endif