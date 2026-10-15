#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "raylib.h"
#include "../include/constants.hpp"

typedef struct {
    bool quit;
} GameState;

void gameStart(GameState& game);
void gameProcess(GameState& game);
void gameDraw(GameState& game);
void gameOver(GameState& game);

#endif
