#ifndef __INPUT_MANAGER__
#define __INPUT_MANAGER__
#define INCLUDE_SDL
#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#include <unordered_map>
#include "SDL_include.hpp"

/**
 * Input Singleton
 * Handles all SDL poll events and enables releasing/holding keys.
 * */
class InputManager {
    private:
        bool mouseState[6];
        int mouseUpdate[6];
        std::unordered_map<int, bool> keyState;
        std::unordered_map<int, int> keyUpdate;
        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;

        InputManager();
        ~InputManager();

    public:
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();
        static InputManager& GetInstance();
};

#endif