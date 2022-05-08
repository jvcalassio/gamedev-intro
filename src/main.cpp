#include <iostream>
#include "../include/Game.hpp"
#include "../include/TitleState.hpp"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    TitleState* title = new TitleState();
    game.Push(title);
    game.Run();
    return 0;
}