#include "../include/game.hpp"

void gameStart(Game& game){
    game.quit = false;
}

void gameProcess(Game& game){
    if (IsKeyPressed(KEY_ESCAPE)) game.quit = true;

    switch(game.state) {

        case MENU:
            // menuProcess();
        break;

        case HOW_TO_PLAY:
            // tutorialProcess();
        break;

        case HISTORY:
            // historyProcess();
        break;

        case SETTINGS:
            // settingsProcess();
        break;

        case PLAYING:
            // matchProcess();
        break;

    }
}

void gameOver(Game& game){
    return;
}
