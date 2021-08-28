#ifndef __GAME__
#define __GAME__
#include <string>
#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.hpp"

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