/*
    WINDOWS COMPILING: g++ -o dado_burger src/*.cpp -Wall -std=c++17 -I C:/raylib/raylib/src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm
*/

// #include "../include/constants.hpp"
// #include "../include/game.hpp"
// #include "../include/data_structures.hpp"
#include "../include/graphics.hpp"
// #include "raylib.h"

int main(int argc, char* argv[]) {
    Game game;

    gameStart(game);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dado Burger");
    SetTargetFPS(FPS);

    while (!WindowShouldClose() && !game.quit) {
        gameProcess(game);
        gameDraw(game);
    }

    gameOver(game);
    CloseWindow();

    return 0;
}
