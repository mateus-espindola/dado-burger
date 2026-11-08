#include <cstdio>
#include <cmath>

#include "../include/buttons.hpp"
#include "../include/match.hpp"    // para STATE_QUANTITY, PREPARE, BOARD, OVEN
#include "../include/button_constants.hpp"

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

static void setButton(Button &b, float x, float y, float w, float h, const char *text, ButtonType type) {
    b.type  = type;   // faltava: o parâmetro type não estava sendo usado
    b.shape = { x, y, w, h };
    snprintf(b.text, sizeof(b.text), "%s", text);
}

void declareButtons(ButtonVec *screens) {
    // static: os arrays vivem até o fim do programa
    static Button kitchenBut[BUTTONS_KITCHEN];
    static Button fridgeBut[BUTTONS_FRIDGE];
    static Button prepareBut[BUTTONS_PREPARE];
    static Button boardBut[BUTTONS_BOARD];
    static Button ovenBut[BUTTONS_OVEN];

    screens[KITCHEN] = { kitchenBut, BUTTONS_KITCHEN };
    screens[FRIDGE]  = { fridgeBut,  BUTTONS_FRIDGE  };
    screens[PREPARE] = { prepareBut, BUTTONS_PREPARE };
    screens[BOARD]   = { boardBut,   BUTTONS_BOARD   };
    screens[OVEN]    = { ovenBut,    BUTTONS_OVEN    };

    setButton(kitchenBut[0], PREPARE_LEFT_X, PREPARE_LEFT_Y, PREPARE_LEFT_W, PREPARE_LEFT_H, "PREPARE", CLICK);
    setButton(kitchenBut[1], BOARD_LEFT_X,   BOARD_LEFT_Y,   BOARD_LEFT_W,   BOARD_LEFT_H,   "BOARD",   CLICK);
    setButton(kitchenBut[2], OVEN_LEFT_X,    OVEN_LEFT_Y,    OVEN_LEFT_W,    OVEN_LEFT_H,    "OVEN",    CLICK);

    setButton(fridgeBut[0], TOMATO_LEFT_X, TOMATO_LEFT_Y, TOMATO_LEFT_W, TOMATO_LEFT_H, "TOMATO", PICK);
    setButton(fridgeBut[1], LETUCE_LEFT_X, LETUCE_LEFT_Y, LETUCE_LEFT_W, LETUCE_LEFT_H, "LETUCE", PICK);
}

int nearestButtonIndex(const float playerX, const ButtonVec screen) {
    int nearest = -1;
    float bestDist = INFINITY;

    for (int i = 0; i < screen.size; i++) {

        const Button &b = screen.buttons[i];

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


// void checkMouseButCollision(const Vector2& mouse, Button buttons, int size){
//     for(int i = 0)
// }

void processClick(){

}

int findButtonUnderMouse(Vector2 mouse, const ButtonVec &screen, Camera2D camera){

    Vector2 world = GetScreenToWorld2D(mouse, camera);

    for (int i = screen.size - 1; i >= 0; i--){
        const Rectangle &r = screen.buttons[i].shape;

        bool in_x = world.x >= r.x && world.x <= r.x + r.width;
        bool in_y = world.y >= r.y && world.y <= r.y + r.height;

        if (in_x && in_y) return i;
    }
    return -1;
}


