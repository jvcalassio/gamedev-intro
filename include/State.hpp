#ifndef __STATE__
#define __STATE__
#include "Sprite.hpp"
#include "Music.hpp"

class State {
    private:
        Sprite* bg;
        Music* music;
        bool quitRequested;

    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif