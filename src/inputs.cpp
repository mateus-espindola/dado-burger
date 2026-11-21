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



static bool isCookable(IngredientType t) {
    return t == MEAT || t == VEGAN_PROTEIN || t == BACON
        || t == EGG  || t == SWISS_CHEESE  || t == CHEDDAR;
}

bool isCuttable(IngredientType t) {
    return t == TOMATO || t == ONION;
}
bool canFlip(IngredientType t){
    return t == MEAT || t == VEGAN_PROTEIN;
}

bool canInsert(MatchScreen screen, IngredientType type) {
    switch (screen) {
        case OVEN:  return isCookable(type);
        case BOARD: return isCuttable(type);
        default:    return false;   // outras telas não aceitam INSERT
    }
}

void transferBetweenStacks(Stack& orig, Stack& dest){
    Ingredient ing;
    stack_pop(orig, ing);
    stack_push(dest, ing);
}

// Move todos os itens, preservando a ordem (pop do topo de uma, push no topo da outra)
void transferAllBetweenStacks(Stack& orig, Stack& dest){
    while (orig.size > 0) {
        transferBetweenStacks(orig, dest);
    }
}


void processInputButAction(Ingredient& ing, const MatchScreen& screen){
    switch(screen){
        case OVEN:
            flipMeat(ing);
        break;
        case BOARD:
            cutIngredient(ing);
        break;
        default: break;
    }
}



void processButClick(Match& match, Button& button) {
    Player& player = match.player;

    Stack& inventory = player.inventory[player.selectedSlot];
    Stack& butStack = button.target;

    switch (button.type) {
        case CLICK:
            if (std::strcmp(button.text, COSTUMER_BELL_TEXT) == 0) {
                callCostumer(match.costumer_line, match.costumer_counter);
            } // Handles the costumer bell
            else {
                match.screen = screenFromName(button.text);
            } // Handles the screen changes
        break;

        case PICK:
            if(inventory.size < inventory.capacity){
                Ingredient ing;
                initIngredient(ing, button.text[0]);
                //The function stack_push already incremetns the size and assigns the type
                stack_push(inventory, ing);
                //SÓ USAR ESSE PRINTF SE EXTREMAMENTE NECESSÁRIO PARA DEBUG. ELE PODE ORIGINAR ACESSO À PONTEIRO NULL E CRASHAR A PORRA TODA
                // printf("ITEM: %d\n", match.player.inventory->top->data.type);
                // printf("%c ", button.text[0]);
                // printf("%d ", inventory.size);
                // printf("%d\n", inventory.type);
            }

        break;

        case DROP:
            if(inventory.size > 0){
                //The function stack_push already incremetns the size and assigns the type
                stack_pop(inventory);
            }
        break;

        case INSERT:
            if(butStack.size == 0){
                if(inventory.size > 0 && canInsert(match.screen, inventory.type)){
                    transferBetweenStacks(inventory, butStack);
                    butStack.top->data.cook_state.cooking = true;
                }
            }
            else{ //if(butStack.size > 0){}
                Ingredient& ing = butStack.top->data;
                if(IsKeyDown(KEY_LEFT_CONTROL) && canFlip(ing.type)){
                    processInputButAction(ing, match.screen);
                }
                if(inventory.size == 0 && !IsKeyDown(KEY_LEFT_CONTROL)){
                    ing.cook_state.cooking = false;
                    transferBetweenStacks(butStack, inventory);
                }
            }
        break;

        case STACK: {
            if (inventory.type == NONE) {
                if (butStack.type == BURGER) {
                    inventory.capacity = butStack.size;
                    transferAllBetweenStacks(butStack, inventory);
                    inventory.type = BURGER;

                    break;
                }

                if (butStack.type == NONE) break;

                else {
                    Ingredient aux;
                    stack_pop(butStack, aux);
                    stack_push(inventory, aux);

                    break;
                }
            }
            if (inventory.type == BURGER) {
                if (butStack.type == BURGER) {
                    bool inventoryBigger = inventory.capacity >= butStack.capacity;
                    int newCapacity = butStack.capacity;

                    if (inventoryBigger) {
                        transferAllBetweenStacks(butStack, inventory);
                        inventory.capacity = newCapacity;
                    }
                    if (!inventoryBigger) {
                        inventory.capacity = newCapacity;
                        transferAllBetweenStacks(butStack, inventory);
                    }
                    break;
                }

                if (butStack.type == NONE) {
                    transferAllBetweenStacks(inventory, butStack);
                    butStack.type = BURGER;
                    inventory.capacity = 1;
                    break;
                }

                else break;
            }
            else {
                if (butStack.type == BURGER) {
                    Ingredient aux;
                    stack_pop(inventory, aux);
                    stack_push(butStack, aux);

                    break;
                }

                if (butStack.type == NONE) {
                    Ingredient aux;
                    stack_pop(inventory, aux);
                    stack_push(butStack, aux);

                    if (aux.type == LOWER_BREAD) butStack.type = BURGER;

                    break;
                }

                else {
                    if (butStack.type == inventory.type) {
                        Ingredient aux;
                        stack_pop(inventory, aux);
                        stack_push(butStack, aux);

                        break;
                    }

                    break;
                }
            }
        }
    }
}
