#include <cstdio>

#include "../include/graphics.hpp"
#include "../include/camera.hpp"


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

    BeginMode2D(match.camera);
        playerDraw(match.player);
        DrawRectangle(1000, 300, 30, 30, BLACK);
        printf("%f, %f\n", match.player.pos.x, match.player.pos.y);
    EndMode2D();
    switch(match.state){

        case PAUSED:

        break;

        case DEFEAT:

        break;

        case VICTORY:

        break;

    }

    
        
}

void playerDraw(Player& player) {
    DrawCircleV(player.pos, 25, RED);
}