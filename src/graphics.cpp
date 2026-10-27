#include "../include/graphics.hpp"



void gameDraw(Game &game){
    BeginDrawing();
    ClearBackground(RAYWHITE);

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
            // DrawTexture(game.spritesheet.start->data.texture, 0, 0, WHITE);
            matchDraw(game.current_match);
        break;

    }
    EndDrawing();
}

void matchDraw(Match& match){
    switch(match.state){

        case PAUSED:

        break;

        case DEFEAT:

        break;

        case VICTORY:

        break;

    }

    // BeginMode2D(match.camera);
        playerDraw(match.player);
    // EndMode2D;
}

void playerDraw(Player& player) {
    DrawCircleV(player.pos, 25, RED);
}