/*
    WINDOWS COMPILING: g++ -o dado_burger src/*.cpp -Wall -std=c++17 -I C:/raylib/raylib/src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm
*/

// #include "../include/constants.hpp"
#include "../include/game.hpp"
// #include "../include/data_structures.hpp"
#include "../include/graphics.hpp"
#include "../include/graphic_constants.hpp"
// #include "raylib.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf ( stderr , " Uso : %s < pedidos > < historico >\n" , argv[0]) ;
        return 1;
    }

    FILE * fp = fopen ( argv[1] , "r") ; /* abre o arquivo de pedidos */
    FILE * fh = fopen ( argv[2] , "r") ; /* abre o arquivo de historico */

    Game game = {};
    snprintf(game.historicoPath, sizeof(game.historicoPath), "%s", argv[2]);

    bool files_read = readFiles(game, fp, fh);
    if (!files_read) return 1;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dado Burger");
    SetTargetFPS(FPS);

    declareButtons(game.current_match.buttonsVec);
    gameStart(game);

    while (!WindowShouldClose() && !game.quit) {
        gameProcess(game);
        // gameDraw(game);
    }

    gameOver(game);
    CloseWindow();

    return 0;
}
