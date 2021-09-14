#ifndef __MUSIC__
#define __MUSIC__
#include <string>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {
    private:
        Mix_Music* music;

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