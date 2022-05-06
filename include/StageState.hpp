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
 * Controls current game screen and entities
 * */
class StageState : public State {
    private:
        //Sprite* bg;
        Music* backgroundMusic;
        //bool quitRequested;
        //bool started;
        //std::vector<std::shared_ptr<GameObject>> objectArray;
        TileSet* tileSet;

    public:
        StageState();
        ~StageState();
        //void Start();
        //std::weak_ptr<GameObject> AddObject(GameObject* go);
        //std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};

#endif