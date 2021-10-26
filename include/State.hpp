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
        bool started;
        std::vector<std::shared_ptr<GameObject>> objectArray;

    public:
        State();
        ~State();
        void Start();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif