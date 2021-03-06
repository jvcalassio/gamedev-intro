#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/SDL_include.hpp"
#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/InputManager.hpp"

Game* Game::instance = nullptr;

/**
 * Provides the global game instance
 * Creates a new one, if it's not instantiated yet
 * */
Game& Game::GetInstance() {
    if(instance != nullptr) {
        return *instance;
    }
    instance = new Game(std::string("João Victor Calassio - 18/0033808"), 1024, 600);
    return *instance;
}

/**
 * Initializes all the SDL2 functions, along with
 * SDL2_image, SDL2_mixer
 * Exits if there's any error on loading SDL2
 * Creates the first state
 * */
Game::Game(std::string title, int width, int height) {
    if(instance != nullptr) {
        std::cout << "ih deu erro" << std::endl;
        exit(0);
    } else {
        instance = this;
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << "ih deu erro ao iniciar o sdl: " << SDL_GetError() << std::endl;
        exit(0);
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cout << "ih deu erro ao iniciar o sdl image: " << SDL_GetError() << std::endl;
        exit(0);
    }

    if(TTF_Init() != 0) {
        std::cout << "ih deu erro ao inicial o sdl ttf: " << SDL_GetError() << std::endl;
        exit(0);
    }

    Mix_Init(MIX_INIT_OGG);
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cout << "ih deu erro ao iniciar o sdl mixer: " << SDL_GetError() << std::endl;
        exit(0);
    }
    Mix_AllocateChannels(32);
    Mix_VolumeMusic(20);
    Mix_Volume(-1, 25);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    storedState = nullptr;

    if(window == nullptr || renderer == nullptr) {
        std::cout << "ih deu erro na janela: " << SDL_GetError() << std::endl;
        exit(0);
    }

    srand(time(NULL));

    frameStart = 0;
    this->CalculateDeltaTime();
}

/**
 * Unloads SDL2 functions
 * */
Game::~Game() {
    if(storedState != nullptr) {
        storedState = nullptr;
    }

    while(!stateStack.empty()) {
        stateStack.pop();
    }

    // unloads resources
    Resources::ClearImages();
    Resources::ClearSounds();
    Resources::ClearMusics();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

State& Game::GetCurrentState() {
    return *(stateStack.top().get());
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

float Game::GetDeltaTime() {
    return dt;
}

/**
 * Delta time = time between frames
 * */
void Game::CalculateDeltaTime() {
    int curr = SDL_GetTicks();
    dt = ( (float) (curr - frameStart) / 1000.0 );
    frameStart = curr;
}

/**
 * Main Game Loop
 * */
void Game::Run() {
    if(storedState == nullptr) {
        return;
    }

    stateStack.push(std::unique_ptr<State>(storedState));
    stateStack.top().get()->Start();
    storedState = nullptr;
    
    InputManager& inp = InputManager::GetInstance();

    while(!stateStack.empty()) {
        if(stateStack.top().get()->QuitRequested()) {
            break;
        }

        if(stateStack.top().get()->PopRequested()) {
            stateStack.pop();

            if(!stateStack.empty()) {
                stateStack.top().get()->Resume();
            }
        }

        if(storedState != nullptr) {
            if(!stateStack.empty()) {
                stateStack.top().get()->Pause();
            }
            stateStack.push(std::unique_ptr<State>(storedState));
            stateStack.top().get()->Start();
            storedState = nullptr;
        }

        this->CalculateDeltaTime();
        inp.Update();
        
        if(!stateStack.empty()) {
            this->GetCurrentState().Update(dt);
            this->GetCurrentState().Render();
        }
        SDL_RenderPresent(renderer);
        
        SDL_Delay(16);
    }

    while(!stateStack.empty()) {
        stateStack.pop();
    }

    // unloads resources
    Resources::ClearImages();
    Resources::ClearSounds();
    Resources::ClearMusics();
}

void Game::Push(State* state) {
    storedState = state;
}