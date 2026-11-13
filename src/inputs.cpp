#include <cstdio>
#include <cstring>

#include "../include/inputs.hpp"
#include "../include/tads.hpp"
#include "../include/food.hpp"
// #include "match.hpp"

Vector2 findMousePos(){
    return GetMousePosition();
}

bool mouseKeyLeftClicked(){
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool keyUpClicked(){
    return IsKeyPressed(KEY_UP);
}

bool keyDownClicked(){
    return IsKeyPressed(KEY_DOWN);
}

int changeInvSlot(){
    if(IsKeyPressed(KEY_ONE)) return 0;
    if(IsKeyPressed(KEY_TWO)) return 1;
    if(IsKeyPressed(KEY_THREE)) return 2;
    return -1;
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


void processButClick(Match& match, const Button& button) {
    Player& player = match.player;

    Slot *inventory = player.inventory;
    int slot = player.selectedSlot;

    switch (button.type) {
        case CLICK:
            match.screen = screenFromName(button.text);
        break;

        case PICK:
            // if (button.target == nullptr) {
            //     printf("ERRO: button.target e nullptr!\n");
            //     return;
            // }
            if(inventory[slot].count < inventory[slot].capacity){
                Ingredient ing;
                initIngredient(ing, button.text[0]);
                stack_push(inventory[slot].items, ing);
                inventory[slot].count++;
                inventory[slot].type = ing.type;
                //SÓ USAR ESSE PRINTF SE EXTREMAMENTE NECESSÁRIO PARA DEBUG. ELE PODE ORIGINAR ACESSO À PONTEIRO NULL E CRASHAR A PORRA TODA
                // printf("ITEM: %d\n", match.player.inventory->items.top->data.type);
                printf("%c\n", button.text[0]);
            }

        break;
        case DROP:
            if(inventory[slot].count > 0){
                stack_pop(inventory[slot].items);
                inventory[slot].count--;
                if(inventory[slot].count == 0) inventory[slot].type = NONE;
            }
        break;

        case INSERT:
        case STACK:
            if (button.target == nullptr) return;   // botão mal configurado
            // usa player.inventory[...] como origem e *button.target como destino
        break;
    }
}


// void processButClick(MatchScreen& matchScreen, const ButtonVec& screen, int clickInd){
//     Button &button = screen.buttons[clickInd];
//     switch(button.type){
//         case CLICK:
//             matchScreen = screenFromName(button.text);
//         break;

//         case PICK:

//         break;

//         case DROP:

//         break;

//         case INSERT:

//         break;

//         case STACK:

//         break;
//     }
// }
