#ifndef __GAME__
#define __GAME__
#define INCLUDE_SDL
#include <string>
#include "SDL_include.h"
#include "State.hpp"

/**
 * Main game class
 * Manages the gameloop; holds window and renderer instances
 * Starts SDL2 functionalities
 * Singleton
 * */
class Game {
    private:
        Game(std::string title, int width, int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};

#endif