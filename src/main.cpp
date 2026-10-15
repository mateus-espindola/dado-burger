#include "../include/game.hpp"
#include "raylib.h"

int main(int argc, char* argv[]) {
    GameState game;

    gameStart(game);

    InitWindow(JANELA_LARGURA, JANELA_ALTURA, "Dado Burger");
    SetTargetFPS(FPS);

    while (!WindowShouldClose() && !game.quit) {
        gameProcess(game);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        gameDraw(game);
        EndDrawing();
    }

    gameOver(game);
    CloseWindow();

    return 0;
}
