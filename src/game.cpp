#include "../include/game.hpp"
#include "raylib.h"

void gameStart(Game& game){
    game.quit = false;
}

void gameProcess(Game& game){
    if (IsKeyPressed(KEY_Q)) game.quit = true;

    switch(game.current_match.camera){
        case COUNTER:
            counter_features();
        
        break;
        
        case KITCHEN:
            kitchen_features();

        break;

        case PREPARE:
            prepare_features();

        break;
    }

}

void gameDraw(Game &game){

    switch(game.GameState) {

        case MENU:

        break;

        case HOW_TO_PLAY:

        break;

        case HISTORY:

        break;

        case SETTINGS:

        break;

        case PLAYING:

        break;

    }

}

void matchDraw(Game& game){
    BeginDrawing();

    switch(game.current_match.matchState){

        case PAUSED:
            
        break;

        case DEFEAT:

        break;

        case VICTORY:

        break;

        case COUNTER:
            draw_counter();
        
        break;
        
        case KITCHEN:
            draw_kitchen();

        break;

        case PREPARE:
            draw_prepare();

        break;
    }


    EndDrawing();
    return;
    //Pausa
    //Cozinha
    //Balcao

    //pausa:
        //antigo_enum
        //desenhar bagulho da pausa
}

void gameOver(Game& game){
    return;
}
