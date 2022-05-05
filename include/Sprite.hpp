#ifndef __SPRITE__
#define __SPRITE__
#define INCLUDE_SDL
#include <string>
#include "SDL_include.h"
#include "Component.hpp"
#include "Vec2.hpp"
#include "Timer.hpp"

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
        Vec2 scale;

        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;

        Timer selfDestructCount;
        float secondsToSelfDestruct;

    public:
        Sprite(GameObject& associated, int frameCount = 1, 
                float frameTime = 1.0f, float secondsToSelfDestruct = 0.0f);
        explicit Sprite(GameObject& associated, std::string file, int frameCount = 1, 
                float frameTime = 1.0f, float secondsToSelfDestruct = 0.0f);
        ~Sprite();
        void Start();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        void Render(float x, float y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(std::string type);
        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
};

#endif