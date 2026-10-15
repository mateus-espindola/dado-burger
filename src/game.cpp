#include "../include/game.hpp"
#include "raylib.h"

void gameStart(GameState& game){
    game.quit = false;
}

void gameProcess(GameState& game){
    if (IsKeyPressed(KEY_Q)) game.quit = true;
}

void gameDraw(GameState& game){
    return;
}

void gameOver(GameState& game){
    return;
}
