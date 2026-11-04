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
};