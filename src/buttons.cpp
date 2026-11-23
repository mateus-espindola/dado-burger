#include <cstdio>
#include <cmath>

#include "../include/buttons.hpp"
// #include "match_enums.hpp"
// #include "../include/match.hpp"    // para STATE_QUANTITY, PREPARE, BOARD, OVEN
#include "../include/button_constants.hpp"
#include "../include/graphic_constants.hpp"
#include "raylib.h"

int buttonTargetCapacityOf(ButtonType type){
    switch(type){
        case INSERT: return 1;
        case STACK:
        case READIES_STACK: return 10;
        case HEAP: return 0; // HEAP usa b.heap, nao b.target
        default: return 0;
    }
}

// void zeroButTarget(Button b){
//     b.targetSize = 0;
//     b.targetType = NONE;
// }

void setButton(Button &b, float x, float y, float w, float h, const char *text, ButtonType type) {
    b.type  = type;
    b.shape = { x, y, w, h };
    snprintf(b.text, sizeof(b.text), "%s", text);
    // b.target = nullptr;
    stack_init(b.target);
    b.target.capacity = buttonTargetCapacityOf(type);
    b.target.size = 0;
    b.target.type = NONE;

    initializeHeap(b.heap);
}

void correctButName(Button *b){

    // Button &b = bVec.buttons[bVec.size];
    snprintf(b[0].text, sizeof(b[0].text), "%s", "EGGS");
    snprintf(b[1].text, sizeof(b[1].text), "%s", "LETUCE");
    snprintf(b[2].text, sizeof(b[2].text), "%s", "TOMATO");
    snprintf(b[3].text, sizeof(b[3].text), "%s", "ONION");
    snprintf(b[4].text, sizeof(b[4].text), "%s", "MEAT");
    snprintf(b[5].text, sizeof(b[5].text), "%s", "BACON");
    snprintf(b[6].text, sizeof(b[6].text), "%s", "SWISS CHEESE");
    snprintf(b[7].text, sizeof(b[7].text), "%s", "CHEDDAR");

}

void setPrepSaladButType(Button *buttons, int startInd){
    buttons[startInd + 0].target.type = SWISS_CHEESE;
    buttons[startInd + 1].target.type = CHEDDAR;
    buttons[startInd + 2].target.type = LETTUCE;
    buttons[startInd + 3].target.type = TOMATO;
    buttons[startInd + 4].target.type = ONION;
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

    declarePauseButtons(screenButtons[PAUSED]);

    setButton(kitchenBut[0], PREPARE_LEFT_X, PREPARE_LEFT_Y, PREPARE_LEFT_W, PREPARE_LEFT_H, "PREPARE", CLICK);
    setButton(kitchenBut[1], BOARD_LEFT_X,   BOARD_LEFT_Y,   BOARD_LEFT_W,   BOARD_LEFT_H,   "BOARD",   CLICK);
    setButton(kitchenBut[2], OVEN_LEFT_X,    OVEN_LEFT_Y,    OVEN_LEFT_W,    OVEN_LEFT_H,    "OVEN",    CLICK);
    setButton(kitchenBut[3], TRASH_KITCHEN_LEFT_X, TRASH_KITCHEN_LEFT_Y, TRASH_KITCHEN_LEFT_W, TRASH_KITCHEN_LEFT_H, "TRASH", DROP);
    setButton(kitchenBut[4], COSTUMER_BELL_LEFT_X, COSTUMER_BELL_LEFT_Y, COSTUMER_BELL_WIDTH, COSTUMER_BELL_HEIGHT, COSTUMER_BELL_TEXT, CLICK);

    setButton(fridgeBut[0], MEAT_LEFT_X, MEAT_LEFT_Y, MEAT_LEFT_W, MEAT_LEFT_H, "MEAT", PICK);
    setButton(fridgeBut[1], BACON_LEFT_X, BACON_LEFT_Y, BACON_LEFT_W, BACON_LEFT_H, "BACON", PICK);
    setButton(fridgeBut[2], TOMATO_LEFT_X, TOMATO_LEFT_Y, TOMATO_LEFT_W, TOMATO_LEFT_H, "TOMATO", PICK);
    setButton(fridgeBut[3], SWISS_CHEESE_LEFT_X, SWISS_CHEESE_LEFT_Y, SWISS_CHEESE_LEFT_W, SWISS_CHEESE_LEFT_H, "SWISS CHEESE", PICK);
    setButton(fridgeBut[4], EGGS_LEFT_X, EGGS_LEFT_Y, EGGS_LEFT_W, EGGS_LEFT_H, "EGGS", PICK);
    setButton(fridgeBut[5], ONION_LEFT_X, ONION_LEFT_Y, ONION_LEFT_W, ONION_LEFT_H, "ONION", PICK);
    setButton(fridgeBut[6], LETTUCE_LEFT_X, LETTUCE_LEFT_Y, LETTUCE_LEFT_W, LETTUCE_LEFT_H, "LETTUCE", PICK);
    setButton(fridgeBut[7], CHEDDAR_LEFT_X, CHEDDAR_LEFT_Y, CHEDDAR_LEFT_W, CHEDDAR_LEFT_H, "CHEDDAR", PICK);
    setButton(fridgeBut[8], TRASH_FRIDGE_LEFT_X, TRASH_FRIDGE_LEFT_Y, TRASH_FRIDGE_LEFT_W, TRASH_FRIDGE_LEFT_H, "TRASH", DROP);

    int prepare_start_index = 0;
    prepare_start_index = setSquareButtons(prepareBut, prepare_start_index, 5, PREPARE_SALAD_BUT_DELTA + PREPARE_SALAD_BUT_WIDTH, prepare_salad_button_rect, "SALAD", STACK, false);
    setPrepSaladButType(prepareBut, 0);
    {
        float bottleDelta = PREPARE_BOTTLE_BUT_DELTA + PREPARE_BOTTLE_BUT_HEIGHT;
        setButton(prepareBut[prepare_start_index],     prepare_bottle_button_rect.x, prepare_bottle_button_rect.y,                 prepare_bottle_button_rect.width, prepare_bottle_button_rect.height, "KETCHUP", CLICK);
        setButton(prepareBut[prepare_start_index + 1], prepare_bottle_button_rect.x, prepare_bottle_button_rect.y + bottleDelta,     prepare_bottle_button_rect.width, prepare_bottle_button_rect.height, "MUSTARD", CLICK);
        setButton(prepareBut[prepare_start_index + 2], prepare_bottle_button_rect.x, prepare_bottle_button_rect.y + 2 * bottleDelta, prepare_bottle_button_rect.width, prepare_bottle_button_rect.height, "PICKLES", CLICK);
        prepare_start_index += 3;
    }
    prepare_start_index = setSquareButtons(prepareBut, prepare_start_index, 3, PREPARE_PROTEIN_BUT_DELTA + PREPARE_PROTEIN_BUT_HEIGHT, prepare_protein_button_rect, "PROTEIN", HEAP, true);
    for(int i = 0; i < 3; i++){
        
    }
    {
        Rectangle protein_col2_rect = prepare_protein_button_rect;
        protein_col2_rect.x -= PREPARE_PROTEIN_BUT_WIDTH + PREPARE_PROTEIN_BUT_DELTA_X; // pra dentro da tela, nao pra fora
        protein_col2_rect.y = (WINDOW_HEIGHT / 2) - (PREPARE_PROTEIN_BUT_HEIGHT + PREPARE_PROTEIN_BUT_DELTA / 2);
        prepare_start_index = setSquareButtons(prepareBut, prepare_start_index, 2, PREPARE_PROTEIN_BUT_DELTA + PREPARE_PROTEIN_BUT_HEIGHT, protein_col2_rect, "PROTEIN", HEAP, true);
    }
    {
        float breadDelta = PREPARE_BREAD_BUT_DELTA + PREPARE_BREAD_BUT_WIDTH;
        setButton(prepareBut[prepare_start_index],     prepare_bread_button_rect.x,             prepare_bread_button_rect.y, prepare_bread_button_rect.width, prepare_bread_button_rect.height, "UPPER BREAD", PICK);
        setButton(prepareBut[prepare_start_index + 1], prepare_bread_button_rect.x + breadDelta, prepare_bread_button_rect.y, prepare_bread_button_rect.width, prepare_bread_button_rect.height, "DOWN BREAD", PICK);
        prepare_start_index += 2;
    }
    setButton(prepareBut[prepare_start_index],     PREPARE_BURGER_LEFT_BUT_LEFT_X,  PREPARE_BURGER_BUT_LEFT_Y, PREPARE_BURGER_BUT_WIDTH, PREPARE_BURGER_BUT_HEIGHT, "BURGER", STACK);
    setButton(prepareBut[prepare_start_index + 1], PREPARE_BURGER_BUT_LEFT_X,       PREPARE_BURGER_BUT_LEFT_Y, PREPARE_BURGER_BUT_WIDTH, PREPARE_BURGER_BUT_HEIGHT, "BURGER", STACK);
    setButton(prepareBut[prepare_start_index + 2], PREPARE_BURGER_RIGHT_BUT_LEFT_X, PREPARE_BURGER_BUT_LEFT_Y, PREPARE_BURGER_BUT_WIDTH, PREPARE_BURGER_BUT_HEIGHT, "BURGER", STACK);
    for(int i = 0; i < 3; i++){
        prepareBut[prepare_start_index + i].target.type = BURGER;
    }
    prepare_start_index += 3;

    int cook_start_index = 0;
    Rectangle rect1 = { OVEN_STACK_FIRTS_BUT_LEFT_X, OVEN_STACK_FIRTS_BUT_LEFT_Y, OVEN_STACK_BUT_WIDTH, OVEN_STACK_BUT_HEIGHT };
    Rectangle rect2 = { OVEN_GRILL_FIRST_BUT_LEFT_X, OVEN_STACK_FIRTS_BUT_LEFT_Y, OVEN_STACK_BUT_WIDTH, OVEN_STACK_BUT_HEIGHT };
    Rectangle rect3 = { OVEN_GRILL_SECOND_BUT_LEFT_X, OVEN_STACK_FIRTS_BUT_LEFT_Y, OVEN_STACK_BUT_WIDTH, OVEN_STACK_BUT_HEIGHT };
    Rectangle rect4 = { OVEN_READIES_BUT_LEFT_X, OVEN_READIES_BUT_LEFT_Y, OVEN_STACK_BUT_WIDTH, OVEN_STACK_BUT_HEIGHT };
    cook_start_index = setSquareButtons(ovenBut, cook_start_index, OVEN_BUTTON_COUNT, OVEN_STACK_BUT_DELTA + OVEN_STACK_BUT_HEIGHT, rect1, "STACK", STACK, true);
    ovenBut[0].target.type = MEAT;
    ovenBut[1].target.type = EGG;
    ovenBut[2].target.type = BACON;

    cook_start_index = setSquareButtons(ovenBut, cook_start_index, OVEN_BUTTON_COUNT, OVEN_STACK_BUT_DELTA + OVEN_STACK_BUT_HEIGHT, rect2, "COOK", INSERT, true);
    cook_start_index = setSquareButtons(ovenBut, cook_start_index, OVEN_BUTTON_COUNT, OVEN_STACK_BUT_DELTA + OVEN_STACK_BUT_HEIGHT, rect3, "COOK", INSERT, true);
    cook_start_index = setSquareButtons(ovenBut, cook_start_index, 1, OVEN_STACK_BUT_DELTA + OVEN_STACK_BUT_HEIGHT, rect4, "READY", READIES_HEAP, true);

    int board_start_index = 0;
    rect1.x -= BOARD_STACK_BUT_DELTA_X;
    board_start_index = setSquareButtons(boardBut, board_start_index, 3, BOARD_STACK_BUT_DELTA_Y + BOARD_STACK_BUT_HEIGHT, rect1, "STACK", STACK, true);
    boardBut[0].target.type = LETTUCE;
    boardBut[1].target.type = TOMATO;
    boardBut[2].target.type = ONION;


    rect1.x += 2*BOARD_STACK_BUT_DELTA_X; // Aproveitar as constantes definidas acima neeeaaahhhhh
    rect1.y = (WINDOW_HEIGHT/2) - (BOARD_STACK_BUT_HEIGHT + BOARD_STACK_BUT_DELTA_Y/2);
    board_start_index = setSquareButtons(boardBut, board_start_index, 2, BOARD_STACK_BUT_DELTA_Y + BOARD_STACK_BUT_HEIGHT, rect1, "STACK", STACK, true);
    boardBut[3].target.type = SWISS_CHEESE;
    boardBut[4].target.type = CHEDDAR;

    board_start_index = setSquareButtons(boardBut, board_start_index, 1, BOARD_STACK_BUT_DELTA_Y + BOARD_STACK_BUT_HEIGHT, rect4, "READY", READIES_STACK, true);
    setButton(boardBut[board_start_index], BOARD_X, BOARD_Y, BOARD_W, BOARD_H, "CUTTING BOARD", INSERT);

}

void declareMenuButtons(ButtonVec &menuButtons) {
    static Button menuBut[BUTTONS_MENU];
    menuButtons = { menuBut, BUTTONS_MENU };

    setButton(menuBut[0], MENU_BUTTON_LEFT_X, MENU_BUTTON_FIRST_Y + 0 * MENU_BUTTON_DELTA, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, "PLAY", CLICK);
    setButton(menuBut[1], MENU_BUTTON_LEFT_X, MENU_BUTTON_FIRST_Y + 1 * MENU_BUTTON_DELTA, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, "HOW TO PLAY", CLICK);
    setButton(menuBut[2], MENU_BUTTON_LEFT_X, MENU_BUTTON_FIRST_Y + 2 * MENU_BUTTON_DELTA, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, "HISTORY", CLICK);
    setButton(menuBut[3], MENU_BUTTON_LEFT_X, MENU_BUTTON_FIRST_Y + 3 * MENU_BUTTON_DELTA, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, "QUIT", CLICK);
}

void declarePauseButtons(ButtonVec &pauseButtons) {
    static Button pauseBut[BUTTONS_PAUSE];
    pauseButtons = { pauseBut, BUTTONS_PAUSE };

    setButton(pauseBut[0], PAUSE_BUTTON_LEFT_X, PAUSE_BUTTON_FIRST_Y + 0 * PAUSE_BUTTON_DELTA, PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT, "RESUME MATCH",  CLICK);
    setButton(pauseBut[1], PAUSE_BUTTON_LEFT_X, PAUSE_BUTTON_FIRST_Y + 1 * PAUSE_BUTTON_DELTA, PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT, "RESTART MATCH", CLICK);
    setButton(pauseBut[2], PAUSE_BUTTON_LEFT_X, PAUSE_BUTTON_FIRST_Y + 2 * PAUSE_BUTTON_DELTA, PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT, "QUIT MATCH",    CLICK);
}

void declareHistoryButtons(ButtonVec &historyButtons) {
    static Button historyBut[BUTTONS_HISTORY];
    historyButtons = { historyBut, BUTTONS_HISTORY };

    setButton(historyBut[0], HISTORY_BACK_BUTTON_X,  HISTORY_BACK_BUTTON_Y, HISTORY_NAV_BUTTON_WIDTH, HISTORY_NAV_BUTTON_HEIGHT, "BACK", CLICK);
    setButton(historyBut[1], HISTORY_FIRST_BUTTON_X, HISTORY_NAV_BUTTON_Y, HISTORY_NAV_BUTTON_WIDTH, HISTORY_NAV_BUTTON_HEIGHT, "<<",   CLICK);
    setButton(historyBut[2], HISTORY_PREV_BUTTON_X,  HISTORY_NAV_BUTTON_Y, HISTORY_NAV_BUTTON_WIDTH, HISTORY_NAV_BUTTON_HEIGHT, "PREV", CLICK);
    setButton(historyBut[3], HISTORY_NEXT_BUTTON_X,  HISTORY_NAV_BUTTON_Y, HISTORY_NAV_BUTTON_WIDTH, HISTORY_NAV_BUTTON_HEIGHT, "NEXT", CLICK);
    setButton(historyBut[4], HISTORY_LAST_BUTTON_X,  HISTORY_NAV_BUTTON_Y, HISTORY_NAV_BUTTON_WIDTH, HISTORY_NAV_BUTTON_HEIGHT, ">>",   CLICK);
    setButton(historyBut[5], HISTORY_SORT_BUTTON_X,  HISTORY_SORT_BUTTON_Y, HISTORY_SORT_BUTTON_WIDTH, HISTORY_SORT_BUTTON_HEIGHT, "SORT: SCORE", CLICK);
}

int findUIButtonUnderMouse(Vector2 mouse, const ButtonVec &buttons) {
    for (int i = buttons.size - 1; i >= 0; i--) {
        if (CheckCollisionPointRec(mouse, buttons.buttons[i].shape)) return i;
    }
    return -1;
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

// void processClick(){

// }

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
