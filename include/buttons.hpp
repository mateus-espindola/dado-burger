#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include "raylib.h"


/* ============================ */
/*            BUTTON            */
/* ============================ */

enum ButtonType {
    BUTTON_MENU,
    BUTTON_OVEN,
    BUTTON_BOARD,
    BUTTON_PREPARE,
    BUTTON_FRIDGE,
    BUTTON_TRASH,
    BUTTON_BELL,
};

struct Button {
    ButtonType type;
    Rectangle shape;
    Vector2 pos;
    Vector2 size;
    char text[20];
};

void declareButtons(Button **buttons, int size);

int nearestButtonIndex(float, Button **buttons);

#endif