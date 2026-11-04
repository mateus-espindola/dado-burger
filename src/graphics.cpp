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

        BeginMode2D(game.current_match.camera);
            spriteDraw(game.sprites[SPR_BACKGROUND], (Vector2){0, 0}, GAME_SCALE, WHITE);
            matchDraw(game.current_match);
        EndMode2D();
        
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
<<<<<<< HEAD

    
        
=======
        // hitboxDraw(match.player.object);
        playerDraw(match.player);
}

Vector2 getSpritePos(Object& object) {
    return (Vector2){object.pos.x - (object.sprite.width * GAME_SCALE) / 2, object.pos.y - (object.sprite.height * GAME_SCALE) / 2};
}

void spriteDraw(Sprite& sprite, Vector2 pos, float scale, Color tint) {
    DrawTexturePro(
        sprite.texture,
        (Rectangle){0, 0, (float)sprite.width, (float)sprite.height},
        (Rectangle){pos.x, pos.y, (float)sprite.width * scale, (float)sprite.height * scale},
        (Vector2){0, 0},
        0.0f,
        tint
    );
}

void warDetirps(Sprite& sprite, Vector2 pos, float scale, Color tint) {
    DrawTexturePro(
        sprite.texture,
        (Rectangle){(float)sprite.width, 0, (float)sprite.width * -1, (float)sprite.height},
        (Rectangle){pos.x, pos.y, (float)sprite.width * scale, (float)sprite.height * scale},
        (Vector2){0, 0},
        0.0f,
        tint
    );
}

void hitboxDraw(Object& object) {
    DrawCircleV(object.pos, object.radius, RED);
>>>>>>> f81ab36a65a1122e1733b2804398d4964509821a
}

void playerDraw(Player& player) {
    Vector2 spritePos = getSpritePos(player.object);

    if (player.direction == DIR_RIGHT) {
        spriteDraw(player.object.sprite, spritePos, GAME_SCALE, WHITE);
    }
    if (player.direction == DIR_LEFT) {
        warDetirps(player.object.sprite, spritePos, (GAME_SCALE * -1), WHITE);
    }
}