#ifndef __MUSIC__
#define __MUSIC__
#define INCLUDE_SDL_MIXER
#include <string>
#include <memory>
#include "SDL_include.hpp"

/**
 * Game Music
 * Manages SDL2 functions for background music
 * */
class Music {
    private:
        std::shared_ptr<Mix_Music> music;

    public:
        Music();
        Music(std::string file);
        ~Music();
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();
};

#endif