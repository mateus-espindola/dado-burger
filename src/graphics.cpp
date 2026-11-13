#include <cstdio>

#include "../include/graphics.hpp"
#include "../include/camera.hpp"
#include "../include/button_constants.hpp"
#include "raylib.h"


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

        drawInventory(match.player);

    EndDrawing();
}

void drawPrepare(Match &match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    const ButtonVec &buttonsVec = match.buttonsVec[match.screen];

    drawButtons(buttonsVec);

    drawButGlow(buttonsVec.buttons[butUnderMouseInd].shape, WHITE, BRIGHTNESS_LAYERS, BRIGHTNESS);

    drawInventory(match.player);

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

void drawBoard(Match match, int butUnderMouseInd) {
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

        drawInventory(match.player);

    EndDrawing();
}




// Grade de círculos pretos, centrados em cada célula da área
static void drawCircleGrid(Rectangle area, int cols, int rows, float radius) {
    float cw = area.width  / cols;
    float ch = area.height / rows;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            DrawCircleV({ area.x + (c + 0.5f) * cw, area.y + (r + 0.5f) * ch }, radius, BLACK);
}

// Grade de quadrados pretos, centrados em cada célula da área
static void drawSquareGrid(Rectangle area, int cols, int rows, float side) {
    float cw = area.width  / cols;
    float ch = area.height / rows;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            Rectangle sq = { area.x + (c + 0.5f) * cw - side / 2,
                             area.y + (r + 0.5f) * ch - side / 2, side, side };
            DrawRectangleRec(sq, BLACK);
        }
}

void drawStove(Match& match, int butUnderMouseInd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        BeginMode2D(match.camera);

            // corpo do fogão (cobre o mundo todo)
            DrawRectangle(0, 0, STOVE_WORLD_WIDTH, STOVE_WORLD_HEIGHT, LIGHTGRAY);

            // 1) chapa à esquerda: 6 círculos (2 colunas x 3 linhas)
            Rectangle plate = { PLATE_X, PANEL_Y, PLATE_W, PANEL_H };
            DrawRectangleRec(plate, DARKGRAY);
            DrawRectangleLinesEx(plate, 6, GRAY);
            drawCircleGrid(plate, 2, 3, 80);

            // 2) espaço do meio: 2 colunas x 3 quadrados
            Rectangle squares = { SQUARES_X, PANEL_Y, SQUARES_W, PANEL_H };
            DrawRectangleRec(squares, GRAY);
            DrawRectangleLinesEx(squares, 6, DARKGRAY);
            drawSquareGrid(squares, 2, 3, 140);

            // 3) seção da direita: 1 coluna x 3 círculos
            Rectangle circles = { CIRCLES_X, PANEL_Y, CIRCLES_W, PANEL_H };
            DrawRectangleRec(circles, GRAY);
            DrawRectangleLinesEx(circles, 6, DARKGRAY);
            drawCircleGrid(circles, 1, 3, 80);

            const ButtonVec &buttonsVec = match.buttonsVec[match.screen];
            drawButtons(buttonsVec);
            drawButGlow(buttonsVec.buttons[butUnderMouseInd].shape, WHITE, BRIGHTNESS_LAYERS, BRIGHTNESS);

        EndMode2D();

        drawInventory(match.player);

    EndDrawing();
}


// Cor do círculo de cada ingrediente
static Color ingredientColor(IngredientType t) {
    switch (t) {
        case LETTUCE: return GREEN;
        case TOMATO:  return RED;
        default:      return BLANK;   // ingrediente sem cor definida ainda
    }
}

void drawInventory(const Player &player) {
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        const Stack &slot = player.inventory[i];

        Rectangle r = { INV_X + i * (INV_SLOT_SIZE + INV_SLOT_GAP), INV_Y,
                        INV_SLOT_SIZE, INV_SLOT_SIZE };

        // fundo meio transparente (todos os slots)
        DrawRectangleRec(r, Fade(BLACK, 0.4f));

        // destaque do slot selecionado
        if (i == player.selectedSlot)
            DrawRectangleLinesEx(r, 3, WHITE);
        else
            DrawRectangleLinesEx(r, 1, Fade(WHITE, 0.4f));

        // item, se houver
        if (slot.size > 0 && slot.type != NONE) {
            Vector2 center = { r.x + r.width / 2, r.y + r.height / 2 };
            DrawCircleV(center, INV_SLOT_SIZE * 0.3f, ingredientColor(slot.type));

            // quantidade no canto inferior direito
            if (slot.size > 1)
                DrawText(TextFormat("%d", slot.size),
                         (int)(r.x + r.width - 22), (int)(r.y + r.height - 22), 20, WHITE);
        }
    }
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

        switch(b.type){
            case STACK:
            Color color;
            if(b.target.size <= (int) (b.target.capacity/4)) color = GREEN;
            else if(b.target.size > (int) (b.target.capacity/4) && b.target.size <= (3*b.target.capacity/4)) color = YELLOW;
            else color = RED;
            DrawText(TextFormat("%d", b.target.size), (int)b.shape.x + 45, (int)b.shape.y - 30, 30, color);

            case INSERT:
            case PICK:
            Vector2 center = {b.shape.x + (b.shape.width/2), b.shape.y + (b.shape.height/2)};
            DrawCircleV(center, b.shape.width/2, ingredientColor(b.target.type));

        }
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
