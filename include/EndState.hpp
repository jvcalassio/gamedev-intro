#ifndef __END_STATE__
#define __END_STATE__
#include "State.hpp"
#include "Music.hpp"

/**
 * End State
 * Controls win/lose screen
 * */
class EndState : public State {
    private:
        Music* backgroundMusic;

    public:
        EndState();
        ~EndState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};

#endif