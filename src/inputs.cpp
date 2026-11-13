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

void transferBetweenStacks(Stack& orig, Stack& dest){
    Ingredient ing;
    stack_pop(orig, ing);
    stack_push(dest, ing);
}


void processButClick(Match& match, Button& button) {
    Player& player = match.player;

    Stack& inventory = player.inventory[player.selectedSlot];
    Stack& butStack = button.target;

    switch (button.type) {
        case CLICK:
            match.screen = screenFromName(button.text);
        break;

        case PICK:
            // if (button.target == nullptr) {
            //     printf("ERRO: button.target e nullptr!\n");
            //     return;
            // }
            if(inventory.size < inventory.capacity){
                Ingredient ing;
                initIngredient(ing, button.text[0]);
                //stack_push already incremetns the size and assigns the type
                stack_push(inventory, ing);
                //SÓ USAR ESSE PRINTF SE EXTREMAMENTE NECESSÁRIO PARA DEBUG. ELE PODE ORIGINAR ACESSO À PONTEIRO NULL E CRASHAR A PORRA TODA
                // printf("ITEM: %d\n", match.player.inventory->top->data.type);
                printf("%c ", button.text[0]);
                printf("%d ", inventory.size);
                printf("%d\n", inventory.type);
            }

        break;

        case DROP:
            if(inventory.size > 0){
                stack_pop(inventory);
                inventory.size--;
                if(inventory.size == 0) inventory.type = NONE;
            }
        break;

        case INSERT:
            if(butStack.size == 0){
                if(inventory.size > 0){
                    transferBetweenStacks(inventory, butStack);
                }
            }
            else{
                if(inventory.size == 0){
                    transferBetweenStacks(butStack, inventory);
                }
            }
        break;

        case STACK:
            printf("Entrou\n");
            // if (button.target == nullptr) return;   // botão mal configurado
            printf("Entrou1\n");
            // usa player.inventory[...] como origem e *button.target como destino
            if(IsKeyDown(KEY_LEFT_SHIFT)){
                printf("Entrou shift\n");
                //Pega o ítem da stack e joga no inventário do player
                if(butStack.type != NONE){
                    if(inventory.size < inventory.capacity){
                        //Only necessary if we implement the player inventory to have more than 1 item per slot
                        if(inventory.type == NONE || inventory.type == butStack.type){
                            transferBetweenStacks(butStack, inventory);
                        }
                    }
                }
            }
            else{
                //Pega o ítem do player e joga no stack
                printf("Entrou not shift\n");
                if(butStack.size < butStack.capacity){
                    if(inventory.type != NONE){
                        if(butStack.type == NONE || inventory.type == butStack.type){
                            transferBetweenStacks(inventory, butStack);
                        }
                    }
                }
            }
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
