/*
    WINDOWS COMPILING: g++ -o dado_burger src/*.cpp -Wall -std=c++17 -I C:/raylib/raylib/src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm
    UBUNTU COMPILING: g++ src/*.cpp -o jogoburger -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
*/

#include "../include/game.hpp"
#include "../include/graphics.hpp"
#include "../include/graphic_constants.hpp"
#include "../include/logs.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <pedidos> <historico>\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "r"); /* abre o arquivo de pedidos */
    FILE* fh = fopen(argv[2], "r"); /* abre o arquivo de historico */

    // novo: sem isso, fopen falho vira crash dentro do readFiles
    if (!fp || !fh) {
        fprintf(stderr, "Erro ao abrir os arquivos de entrada\n");
        if (fp) fclose(fp);
        if (fh) fclose(fh);
        return 1;
    }

    Game game = {};
    snprintf(game.historicoPath, sizeof(game.historicoPath), "%s", argv[2]);

    bool files_read = readFiles(game, fp, fh);
    fclose(fp);   // novo
    fclose(fh);   // novo
    if (!files_read) return 1;

    // novo: 1o momento do log (apos o carregamento).
    // readFiles ja deve ter preenchido g_metrics.avlNodes, avlHeight,
    // avlRotations, loadTime e historyEntries.
    writeLog();

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
