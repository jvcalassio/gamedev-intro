#ifndef __TITLE_STATE__
#define __TITLE_STATE__
#include "State.hpp"

/**
 * Title State
 * Controls menu game screen
 * */
class TitleState : public State {
    public:
        TitleState();
        ~TitleState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};

#endif