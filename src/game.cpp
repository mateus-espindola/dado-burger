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
    //Pausa
    //Cozinha
    //Balcao

    //pausa:
        //antigo_enum
        //desenhar bagulho da pausa
}

void gameOver(GameState& game){
    return;
}
