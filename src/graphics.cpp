#include <cstdio>

#include "../include/graphics.hpp"
#include "../include/camera.hpp"
#include "button_constants.hpp"


// void gameDraw(Game &game){
//     BeginDrawing();
//     ClearBackground(RAYWHITE);

//     switch(game.state) {

//         case MENU:
//             // menuDraw();
//         break;

//         case HOW_TO_PLAY:
//             // tutorialDraw();
//         break;

//         case HISTORY:
//             // historyDraw();
//         break;

//         case SETTINGS:
//             // settingsDraw();
//         break;

//         case PLAYING:

//         BeginMode2D(game.current_match.camera);
//             spriteDraw(game.sprites[SPR_BACKGROUND], (Vector2){0, 0}, GAME_SCALE, WHITE);
//             //drawNearestBut(game.current_match.player, game.current_match.buttons);
//             matchDraw(game.current_match);
//         EndMode2D();
        
//         break;

//     }
//     EndDrawing();
// }


void drawKitchen(Match& match, int butUnderMouseInd){
    BeginDrawing();
    ClearBackground(RAYWHITE);

        const ButtonVec &buttonsVec = match.buttonsVec[match.screen];

        BeginMode2D(match.camera);
            spriteDraw(match.spriteMatch[SPR_BACKGROUND], (Vector2){0, 0}, GAME_SCALE, WHITE);

            int visible = -1;   //Index of the visible button in drawNearesBut

            if(match.screen == FRIDGE){
                drawButtons(buttonsVec);

                if(butUnderMouseInd != -1)
                    drawButGlow(buttonsVec.buttons[butUnderMouseInd].shape, WHITE, BRIGHTNESS_LAYERS, BRIGHTNESS);
            }
            else{
                visible = drawNearestBut(match.player, buttonsVec);
                drawButGlow(buttonsVec.buttons[visible].shape, WHITE, BRIGHTNESS_LAYERS, BRIGHTNESS);
            }


            playerDraw(match.player);

            if(DRAW_HITBOX == 1) hitboxDraw(match.player.object);

        EndMode2D();

    EndDrawing();
}


static void drawStackColumn(float x, int count) {
    float total  = count * STACK_H + (count - 1) * STACK_GAP;
    float startY = WINDOW_WIDTH / 2.0f - total / 2.0f;

    for (int i = 0; i < count; i++) {
        Rectangle r = { x, startY + i * (STACK_H + STACK_GAP), STACK_W, STACK_H };
        DrawRectangleRec(r, BLACK);
    }
}

void drawPrepare(Match match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        // chão e paredes
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, LIGHTGRAY);
        DrawRectangleLinesEx((Rectangle){ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }, 12, DARKGRAY);

        // tábua
        Rectangle board = { BOARD_X, BOARD_Y, BOARD_W, BOARD_H };
        DrawRectangleRec(board, (Color){ 139, 90, 43, 255 });
        DrawRectangleLinesEx(board, 4, DARKBROWN);

        // 3 stacks à esquerda
        drawStackColumn(BOARD_X - STACK_MARGIN - STACK_W, STACKS_LEFT);

        // 2 stacks à direita
        drawStackColumn(BOARD_X + BOARD_W + STACK_MARGIN, STACKS_RIGHT);

    EndDrawing();
}

// void drawPrepare(Match match, int butUnderMouseInd){

// }


// void matchDraw(Match& match){

//     // BeginMode2D(match.camera);

//         playerDraw(match.player);
//         printf("%f, %f\n", match.player.object.pos.x, match.player.object.pos.y);
        
//     // EndMode2D();
//     switch(match.state){

//         case PAUSED:

//         break;

//         case DEFEAT:

//         break;

//         case VICTORY:

//         break;

//     }
//         hitboxDraw(match.player.object);
//         // playerDraw(match.player);
// }

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

void hitboxDraw(const Object& object) {
    DrawCircleV(object.pos, object.radius, RED);
}

//COLOCAR CONST DEPOIS
void playerDraw(Player& player) {
    Vector2 spritePos = getSpritePos(player.object);

    if (player.direction == DIR_RIGHT) {
        spriteDraw(player.object.sprite, spritePos, GAME_SCALE, WHITE);
    }
    if (player.direction == DIR_LEFT) {
        warDetirps(player.object.sprite, spritePos, GAME_SCALE, WHITE);
    }
}

int drawNearestBut(const Player& player, const ButtonVec& screen) {
    // for (int i = 0; i < STATE_QUANTITY; i++) {
    //     if (buttons[i] == nullptr) continue;   // estado sem botões

    //     const Button &b = buttons[i][0];
    //     DrawRectangle((int)b.pos.x, (int)b.pos.y, (int)b.size.x, (int)b.size.y, GRAY);
    //     DrawText(b.text, (int)b.pos.x + 10, (int)b.pos.y + 10, 30, BLACK);
    // }

    int index = nearestButtonIndex(player.object.pos.x, screen);

    if(index != -1){
        const Button &b = screen.buttons[index];
        DrawRectangle((int)b.shape.x, (int)b.shape.y, (int)b.shape.width, (int)b.shape.height, GRAY);
        // drawButGlow(b.shape, WHITE, CAMADAS_DE_BRILHO, BRILHO);
        DrawText(b.text, (int)b.shape.x + 10, (int)b.shape.y + 10, 30, BLACK);
    }

    return index;
}


void drawButtons(const ButtonVec& screen){

    for (int i = 0; i < screen.size; i++) {

        const Button &b = screen.buttons[i];

        DrawRectangle((int)b.shape.x, (int)b.shape.y, (int)b.shape.width, (int)b.shape.height, GRAY);
        // drawButGlow(b.shape, WHITE, CAMADAS_DE_BRILHO, BRILHO);
        DrawText(b.text, (int)b.shape.x + 10, (int)b.shape.y + 10, 30, BLACK);

    }

}

//Camadas: Grossura do brilho. Alpha: O quanto brilha. Ambas são constantes em button_constants.hpp
//Essa função faz os botões brilharem
void drawButGlow(Rectangle r, Color cor, int camadas, float alpha){
    for (int i = 1; i <= camadas; i++)
    {
        Rectangle g = { r.x - i, r.y - i, r.width + i * 2, r.height + i * 2 };
        float a = alpha * (1.0f - (float)i / (camadas + 1));   // some com a distância
        DrawRectangleLinesEx(g, 1, Fade(cor, a));
    }
}