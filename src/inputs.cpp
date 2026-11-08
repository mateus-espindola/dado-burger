#include <cstring>

#include "inputs.hpp"
// #include "match.hpp"

Vector2 findMousePos(){
    return GetMousePosition();
}

bool mouseKeyLeftClicked(){
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}


MatchScreen screenFromName(const char *name)
{
    if (strcmp(name, "KITCHEN") == 0) return KITCHEN;
    if (strcmp(name, "FRIDGE")  == 0) return FRIDGE;
    if (strcmp(name, "OVEN")    == 0) return OVEN;
    if (strcmp(name, "BOARD")   == 0) return BOARD;
    if (strcmp(name, "PREPARE") == 0) return PREPARE;
    return KITCHEN;   // valor padrão se não achar
}


void processButClick(MatchScreen& matchScreen, const ButtonVec& screen, int clickInd){
    Button &button = screen.buttons[clickInd];
    switch(button.type){
        case CLICK:
            matchScreen = screenFromName(button.text);
        break;

        case PICK:

        break;

        case DROP:

        break;

        case INSERT:

        break;

        case STACK:

        break;
    }
}
