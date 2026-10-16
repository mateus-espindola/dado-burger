#include "../include/graphics.hpp"

void gameDraw(Game &game){
    BeginDrawing();

    switch(game.state) {

        case MENU:
            // menuDraw();
        break;

        case HOW_TO_PLAY:
            // tutorialDraw();
        break;

        case HISTORY:
            // historyDraw();
        break;

        case SETTINGS:
            // settingsDraw();
        break;

        case PLAYING:
            // matchDraw();
        break;

    }
    EndDrawing();
}

void matchDraw(Game& game){
    switch(game.current_match.state){

        case PAUSED:

        break;

        case DEFEAT:

        break;

        case VICTORY:

        break;

    }
}
