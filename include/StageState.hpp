#ifndef __STAGE_STATE__
#define __STAGE_STATE__
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "State.hpp"
//#include "Sprite.hpp"
#include "Music.hpp"
#include "TileSet.hpp"

/**
 * Game State
 * Controls game screen and entities
 * */
class StageState : public State {
    private:
        Music* backgroundMusic;
        TileSet* tileSet;

    public:
        StageState();
        ~StageState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};

#endif