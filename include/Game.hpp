#ifndef __GAME__
#define __GAME__
#define INCLUDE_SDL
#include <string>
#include <stack>
#include "SDL_include.h"
#include "State.hpp"
#include "StageState.hpp"

/**
 * Main game class
 * Manages the gameloop; holds window and renderer instances
 * Starts SDL2 functionalities
 * Singleton
 * */
class Game {
    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int frameStart;
        float dt;

        State* storedState;
        std::stack<std::unique_ptr<State>> stateStack;

        Game(std::string title, int width, int height);
        void CalculateDeltaTime();
        
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();
        static Game& GetInstance();
        float GetDeltaTime();
        void Push(State* state);
};

#endif