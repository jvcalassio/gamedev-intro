#ifndef __STAGE_STATE__
#define __STAGE_STATE__
#define ALIEN_COUNT 4
#define ALIEN_MINION_COUNT 6
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "State.hpp"
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