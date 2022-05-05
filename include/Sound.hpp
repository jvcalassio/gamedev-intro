#ifndef __SOUND__
#define __SOUND__
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Component.hpp"

/**
 * Game Sounds
 * Manages SDL2 functions for sound effects
 * You can play multiple sounds at the same time in different channels
 * 
 * Implemented as a Component since it's meant to be used as an
 * element of GameObject
 * */
class Sound : public Component {
    private:
        Mix_Chunk* chunk;
        int channel;
    
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();
        void Start();
        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        bool IsPlaying();
};

#endif