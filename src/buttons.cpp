#include <cstdio>
#include <cmath>

#include "../include/buttons.hpp"
// #include "match_enums.hpp"
// #include "../include/match.hpp"    // para STATE_QUANTITY, PREPARE, BOARD, OVEN
#include "../include/button_constants.hpp"
#include "raylib.h"

// static void setButton(Button &b, float x, float y, float w, float h, const char *text, ButtonType type) {
//     b.shape = { x, y, w, h };
//     // b.pos   = { x, y };
//     // b.size  = { w, h };
//     snprintf(b.text, sizeof(b.text), "%s", text);
// }

// void declareButtons(Button **buttons, int size) {
//     // static: os arrays vivem até o fim do programa
//     static Button kitchenBut[BUTTONS_KITCHEN];
//     static Button fridgeBut[BUTTONS_KITCHEN];
//     static Button prepareBut[BUTTONS_PREPARE];
//     static Button boardBut[BUTTONS_BOARD];
//     static Button ovenBut[BUTTONS_OVEN];

//     buttons[KITCHEN] = kitchenBut;
//     buttons[FRIDGE] = fridgeBut;
//     buttons[PREPARE] = prepareBut;
//     buttons[BOARD]   = boardBut;
//     buttons[OVEN]    = ovenBut;


//     setButton(kitchenBut[0], PREPARE_LEFT_X, PREPARE_LEFT_Y, PREPARE_LEFT_W, PREPARE_LEFT_H, "PREPARE", CLICK);
//     setButton(kitchenBut[1], BOARD_LEFT_X, BOARD_LEFT_Y,   BOARD_LEFT_W,   BOARD_LEFT_H, "BOARD", CLICK);
//     setButton(kitchenBut[2], OVEN_LEFT_X, OVEN_LEFT_Y, OVEN_LEFT_W, OVEN_LEFT_H, "OVEN", CLICK);

//     setButton(fridgeBut[0], TOMATO_LEFT_X, TOMATO_LEFT_Y, TOMATO_LEFT_W, TOMATO_LEFT_H, "TOMATO", PICK);
//     setButton(fridgeBut[1], LETUCE_LEFT_X, LETUCE_LEFT_Y, LETUCE_LEFT_W, LETUCE_LEFT_H, "LETUCE", PICK);


// }

int buttonTargetCapacityOf(ButtonType type){
    switch(type){
        case INSERT: return 1;
        case STACK: return 10;
        default: return 0;
    }
}

static void setButton(Button &b, float x, float y, float w, float h, const char *text, ButtonType type) {
    b.type  = type;
    b.shape = { x, y, w, h };
    snprintf(b.text, sizeof(b.text), "%s", text);
    b.target = nullptr;
    b.targetCapacity = buttonTargetCapacityOf(type);
    b.targetSize = 0;
}

void declareButtons(ButtonVec *screenButtons) {
    // static: os arrays vivem até o fim do programa
    static Button kitchenBut[BUTTONS_KITCHEN];
    static Button fridgeBut[BUTTONS_FRIDGE];
    static Button prepareBut[BUTTONS_PREPARE];
    static Button boardBut[BUTTONS_BOARD];
    static Button ovenBut[BUTTONS_OVEN];

    screenButtons[KITCHEN] = { kitchenBut, BUTTONS_KITCHEN };
    screenButtons[FRIDGE]  = { fridgeBut,  BUTTONS_FRIDGE  };
    screenButtons[PREPARE] = { prepareBut, BUTTONS_PREPARE };
    screenButtons[BOARD]   = { boardBut,   BUTTONS_BOARD   };
    screenButtons[OVEN]    = { ovenBut,    BUTTONS_OVEN    };

    setButton(kitchenBut[0], PREPARE_LEFT_X, PREPARE_LEFT_Y, PREPARE_LEFT_W, PREPARE_LEFT_H, "PREPARE", CLICK);
    setButton(kitchenBut[1], BOARD_LEFT_X,   BOARD_LEFT_Y,   BOARD_LEFT_W,   BOARD_LEFT_H,   "BOARD",   CLICK);
    setButton(kitchenBut[2], OVEN_LEFT_X,    OVEN_LEFT_Y,    OVEN_LEFT_W,    OVEN_LEFT_H,    "OVEN",    CLICK);
    setButton(kitchenBut[3], TRASH_KITCHEN_LEFT_X, TRASH_KITCHEN_LEFT_Y, TRASH_KITCHEN_LEFT_W, TRASH_KITCHEN_LEFT_H, "TRASH", DROP);

    setButton(fridgeBut[0], TOMATO_LEFT_X, TOMATO_LEFT_Y, TOMATO_LEFT_W, TOMATO_LEFT_H, "tTOMATO", PICK);
    setButton(fridgeBut[1], LETUCE_LEFT_X, LETUCE_LEFT_Y, LETUCE_LEFT_W, LETUCE_LEFT_H, "aLETUCE", PICK);
    setButton(fridgeBut[2], TRASH_FRIDGE_LEFT_X, TRASH_FRIDGE_LEFT_Y, TRASH_FRIDGE_LEFT_W, TRASH_FRIDGE_LEFT_H, "TRASH", DROP);

    int startInd = 0;
    Rectangle prepare_salad_button_rect = { PREPARE_SALAD_FIRST_BUT_LEFT_X, PREPARE_SALAD_FIRST_BUT_LEFT_Y, PREPARE_SALAD_BUT_WIDTH, PREPARE_SALAD_BUT_HEIGHT };
    setSquareButtons(prepareBut, startInd, 5, PREPARE_SALAD_BUT_DELTA + PREPARE_SALAD_BUT_WIDTH, prepare_salad_button_rect, "PICK", PICK, false);

    Rectangle rect1 = { COOK_TOP_FRST_CLMN_LEFT_X, COOK_TOP_FRST_Y, OVEN_SQR_BUTTON_SIZE, OVEN_SQR_BUTTON_SIZE };
    Rectangle rect2 = { COOK_TOP_SCND_CLMN_LEFT_X, COOK_TOP_SCND_Y, OVEN_SQR_BUTTON_SIZE, OVEN_SQR_BUTTON_SIZE };
    Rectangle rect3 = { OVEN_STACK_SCND_CLMN_LEFT_X, OVEN_STACK_TOP_SCND_Y, OVEN_SQR_BUTTON_SIZE, OVEN_SQR_BUTTON_SIZE };
    startInd = setSquareButtons(ovenBut, startInd, OVEN_SQR_BUTTON_COUNT, OVEN_SQR_BUTTON_STEP_Y, rect1, "COOK", INSERT, true);
    startInd = setSquareButtons(ovenBut, startInd, OVEN_SQR_BUTTON_COUNT, OVEN_SQR_BUTTON_STEP_Y, rect2, "COOK", INSERT, true);
    startInd = setSquareButtons(ovenBut, startInd, OVEN_SQR_BUTTON_COUNT, OVEN_SQR_BUTTON_STEP_Y, rect3, "STACK", STACK, true);

    // setButton(ovenBut[0], COOK_TOP_1_LEFT_X, COOK_TOP_1_LEFT_Y, COOK_TOP_1_LEFT_W, COOK_TOP_1_LEFT_H, "COOK", INSERT);
    // setButton(ovenBut[1], COOK_TOP_2_LEFT_X, COOK_TOP_2_LEFT_Y, COOK_TOP_2_LEFT_W, COOK_TOP_2_LEFT_H, "COOK", INSERT);
    // setButton(ovenBut[2], COOK_TOP_3_LEFT_X, COOK_TOP_3_LEFT_Y, COOK_TOP_3_LEFT_W, COOK_TOP_3_LEFT_H, "COOK", INSERT);
}

int nearestButtonIndex(const float playerX, const ButtonVec screenButtons) {
    int nearest = -1;
    float bestDist = INFINITY;

    for (int i = 0; i < screenButtons.size; i++) {

        const Button &b = screenButtons.buttons[i];

        // pos é o canto superior esquerdo, então usamos o centro do botão
        float centerX = b.shape.x + b.shape.width / 2.0f;

        // Em um jogo lateral, só a distância horizontal costuma importar
        float dist = fabsf(playerX - centerX);

        if (dist < bestDist && dist <= MAX_ACESS_DIST) {
            bestDist = dist;
            nearest = i;
        }
    }

    return nearest;
}

// x e firstY sao o canto superior esquerdo do primeiro botao
//Devolve o proximo indice livre do botao
// int setCircleButtons(Button *buttons, int startInd, float x, float firstY, const char *text, ButtonType type) {
//     for (int k = 0; k < CIRCLE_BUTTON_COUNT; k++) {
//         setButton(buttons[startInd + k],
//                   x,
//                   firstY + k * CIRCLE_BUTTON_STEP_Y,
//                   CIRCLE_BUTTON_DIAMETER,
//                   CIRCLE_BUTTON_DIAMETER,
//                   text,
//                   type);
//     }
//     return startInd + CIRCLE_BUTTON_COUNT;
// }

int setSquareButtons(Button *buttons, int startInd, int quantity, int delta, Rectangle shape, const char *text, ButtonType type, bool vertical) {
    if (vertical) {
        for (int k = 0; k < quantity; k++) {
            setButton(buttons[startInd + k],
                    shape.x,
                    shape.y + k * delta,
                    shape.width,
                    shape.height,
                    text,
                    type);
        }
        return startInd + quantity;
    }
    else {
        for (int k = 0; k < quantity; k++) {
            setButton(buttons[startInd + k],
                    shape.x+ k * delta,
                    shape.y,
                    shape.width,
                    shape.height,
                    text,
                    type);
        }
        return startInd + quantity;
    }
}


// void checkMouseButCollision(const Vector2& mouse, Button buttons, int size){
//     for(int i = 0)
// }

void processClick(){

}

bool usesCamera(MatchScreen screen) {
    switch (screen) {
        case KITCHEN:
        case FRIDGE:
        case OVEN:   return true;
        default:     return false;
    }
}

int findButtonUnderMouse(Vector2 mouse, const ButtonVec &screenButtons, Camera2D camera, MatchScreen curScreen){

    bool useCamera = usesCamera(curScreen);

    Vector2 point = useCamera ? GetScreenToWorld2D(mouse, camera) : mouse;

    for (int i = screenButtons.size - 1; i >= 0; i--){
        const Rectangle &r = screenButtons.buttons[i].shape;

        bool in_x = point.x >= r.x && point.x <= r.x + r.width;
        bool in_y = point.y >= r.y && point.y <= r.y + r.height;

        if (in_x && in_y) return i;
    }
    return -1;
}
