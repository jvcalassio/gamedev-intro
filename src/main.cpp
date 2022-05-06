#include <iostream>
#include "../include/Game.hpp"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    StageState* stage = new StageState();
    game.Push(stage);
    game.Run();
    return 0;
}