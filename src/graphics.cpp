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
            drawNearestButton(game.current_match.player, game.current_match.buttons);
            matchDraw(game.current_match);
        EndMode2D();
        
        break;

    }
    EndDrawing();
}

void matchDraw(Match& match){

    // BeginMode2D(match.camera);
        playerDraw(match.player);
        printf("%f, %f\n", match.player.object.pos.x, match.player.object.pos.y);
    // EndMode2D();
    switch(match.state){

        case PAUSED:

        break;

        case DEFEAT:

        break;

        case VICTORY:

        break;

    }
        hitboxDraw(match.player.object);
        // playerDraw(match.player);
}

Vector2 getSpritePos(Object& object) {
    return (Vector2){object.pos.x - (object.sprite.width * GAME_SCALE) / 2, object.pos.y - (object.sprite.height * GAME_SCALE) / 2};
}


//MOVIDOS PARA SPRITES.HPP
// void spriteDraw(Sprite& sprite, Vector2 pos, float scale, Color tint) {
//     DrawTexturePro(
//         sprite.texture,
//         (Rectangle){0, 0, (float)sprite.width, (float)sprite.height},
//         (Rectangle){pos.x, pos.y, (float)sprite.width * scale, (float)sprite.height * scale},
//         (Vector2){0, 0},
//         0.0f,
//         tint
//     );
// }

// void warDetirps(Sprite& sprite, Vector2 pos, float scale, Color tint) {
//     DrawTexturePro(
//         sprite.texture,
//         (Rectangle){(float)sprite.width, 0, (float)sprite.width * -1, (float)sprite.height},
//         (Rectangle){pos.x, pos.y, (float)sprite.width * scale, (float)sprite.height * scale},
//         (Vector2){0, 0},
//         0.0f,
//         tint
//     );
// }

void hitboxDraw(Object& object) {
    DrawCircleV(object.pos, object.radius, RED);
}

void playerDraw(Player& player) {
    Vector2 spritePos = getSpritePos(player.object);

    if (player.direction == DIR_RIGHT) {
        spriteDraw(player.object.sprite, spritePos, GAME_SCALE, WHITE);
    }
    if (player.direction == DIR_LEFT) {
        warDetirps(player.object.sprite, spritePos, GAME_SCALE, WHITE);
    }
}

void drawNearestButton(const Player& player, Button **buttons) {
    // for (int i = 0; i < STATE_QUANTITY; i++) {
    //     if (buttons[i] == nullptr) continue;   // estado sem botões

    //     const Button &b = buttons[i][0];
    //     DrawRectangle((int)b.pos.x, (int)b.pos.y, (int)b.size.x, (int)b.size.y, GRAY);
    //     DrawText(b.text, (int)b.pos.x + 10, (int)b.pos.y + 10, 30, BLACK);
    // }

    int index = nearestButtonIndex(player.object.pos.x, buttons);
    printf("x=%.0f index=%d\n", player.object.pos.x, index);
    if(index == -1) return;

    const Button &b = buttons[index][0];
    DrawRectangle((int)b.pos.x, (int)b.pos.y, (int)b.size.x, (int)b.size.y, GRAY);
    DrawText(b.text, (int)b.pos.x + 10, (int)b.pos.y + 10, 30, BLACK);

}