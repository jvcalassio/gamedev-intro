#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include <string>
#include <iostream>

#include "../include/Game.hpp"

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
    if(instance != nullptr) {
        return *instance;
    }
    instance = new Game(std::string("João Victor Calassio - 18/0033808"), 1024, 600);
    return *instance;
}

Game::Game(std::string title, int width, int height) {
    if(instance != nullptr) {
        std::cout << "ih deu erro" << std::endl;
        exit(0);
    } else {
        instance = this;
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << "ih deu erro ao iniciar o sdl" << std::endl;
        exit(0);
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cout << "ih deu erro ao iniciar o sdl image" << std::endl;
        exit(0);
    }

    Mix_Init(MIX_INIT_OGG);
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cout << "ih deu erro ao iniciar o sdl mixer" << std::endl;
        exit(0);
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    state = new State();

    if(window == nullptr || renderer == nullptr) {
        std::cout << "ih deu erro na janela" << std::endl;
        exit(0);
    }
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

State& Game::GetState() {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    while(!state->QuitRequested()) {
        state->Update(1); // 1?
        state->Render();
        SDL_RenderPresent(renderer);
        
        SDL_Delay(33);
    }
}