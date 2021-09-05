#ifndef __STATE__
#define __STATE__
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Music.hpp"

/**
 * Game State
 * Controls current game screen and entities
 * */
class State {
    private:
        //Sprite* bg;
        Music* music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;

        void Input();
        void AddObject(int mouseX, int mouseY);

    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif