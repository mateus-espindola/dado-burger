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
    return IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W);
}

bool keyDownClicked(){
    return IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S);
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
    return t == MEAT || t == VEGAN_PROTEIN || t == BACON || t == EGG;
}

bool isCuttable(IngredientType t) {
    return t == TOMATO || t == ONION || t == SWISS_CHEESE || t == CHEDDAR || t == LETTUCE;
}
bool canFlip(IngredientType t){
    return t == MEAT || t == VEGAN_PROTEIN;
}

// Gate da acao de Ctrl+click dentro do INSERT: cada tela tem sua propria acao manual
bool canCtrlAction(MatchScreen screen, IngredientType type) {
    switch (screen) {
        case OVEN:  return canFlip(type);
        case BOARD: return isCuttable(type);
        default:    return false;
    }
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

// Move todos os itens preservando a ordem. Um pop+push simples inverteria a pilha
// (propriedade classica de pilha), entao desce recursivamente ate o fundo e so
// empilha no destino ao desenrolar, do mais fundo para o topo.
void transferAllBetweenStacks(Stack& orig, Stack& dest){
    if (orig.size == 0) return;

    Ingredient ing;
    stack_pop(orig, ing);

    transferAllBetweenStacks(orig, dest);

    stack_push(dest, ing);
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
        case CLICK: {
            bool isMustard = std::strcmp(button.text, "MUSTARD") == 0;
            bool bottle = std::strcmp(button.text, "KETCHUP") == 0 || isMustard || std::strcmp(button.text, "PICKLES") == 0;
            if (bottle) {
                Stack& burger = match.buttonsVec[PREPARE].buttons[16].target;

                if (burger.type == BURGER) {
                    Ingredient ing;
                    // 'M' mapeia pra MEAT em charToIngType; so o MUSTARD usa o 'm' minusculo pra nao colidir
                    initIngredient(ing, isMustard ? 'm' : button.text[0]);

                    stack_push(burger, ing);
                }

                break;
            }
            if (std::strcmp(button.text, COSTUMER_BELL_TEXT) == 0) {
                callCostumer(match.costumer_line, match.costumer_counter);

                break;
            } // Handles the costumer bell
            else {
                match.screen = screenFromName(button.text);
            } // Handles the screen changes
        break;
        }

        case PICK:
            if(inventory.size < inventory.capacity){
                Ingredient ing;
                initIngredient(ing, button.text[0]);
                stack_push(inventory, ing);
            }

        break;

        case DROP:
            while(inventory.size > 0){
                stack_pop(inventory);
            }
            inventory.capacity = 1;
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
                if(IsKeyDown(KEY_LEFT_CONTROL) && canCtrlAction(match.screen, ing.type)){
                    processInputButAction(ing, match.screen);
                }
                if(inventory.size == 0 && !IsKeyDown(KEY_LEFT_CONTROL)){
                    ing.cook_state.cooking = false;
                    transferBetweenStacks(butStack, inventory);
                }
            }
        break;

        case READIES_HEAP: {
            Heap<Ingredient>& heap = button.heap;

            if (inventory.type == NONE) break; // so recebe, nunca devolve

            // Olha o item no topo da mao ANTES de tirar: depois do pop inventory.type
            // ja vira NONE (capacidade 1) e a checagem nunca passaria.
            Ingredient& top = inventory.top->data;

            bool ingReady = practicalCookingStateOf(top) == RARE || practicalCookingStateOf(top) == MEDIUM_RARE ||
                            practicalCookingStateOf(top) == WELL_DONE || practicalCookingStateOf(top) == READY;

            if (ingReady && heap.size < heap.capacity) {
                Ingredient aux;
                stack_pop(inventory, aux);
                insertHeap(heap, aux);
            }

            break;
        }

        case HEAP: {
            Heap<Ingredient>& heap = button.heap;

            if (inventory.type == NONE) {
                // Mao vazia: pega o ingrediente mais perto de estragar (topo do heap)
                Ingredient ing;
                if (peekMinHeap(heap, ing) && inventory.size < inventory.capacity) {
                    stack_push(inventory, getMinValueHeap(heap));
                }
                break;
            }

            // Mao ocupada: so aceita ingrediente cozinhavel, e o heap so aceita um tipo por vez
            bool typeOk = heap.type == NONE || heap.type == inventory.type;

            if (isCookable(inventory.type) && typeOk && heap.size < heap.capacity) {
                Ingredient aux;
                stack_pop(inventory, aux);
                insertHeap(heap, aux);
            }
        break;
        }

        case READIES_STACK:
            if (inventory.type != NONE && inventory.type != BURGER) {
                Ingredient aux;
                stack_pop(inventory, aux);

                bool ingReady = aux.cook_state.cookInfo[0].cookPoint == READY && aux.cook_state.cookInfo[1].cookPoint == READY;

                if (ingReady && isCuttable(aux.type)) {
                    stack_push(butStack, aux);
                    break;
                }

                stack_push(inventory, aux);
                break;
            }

        case STACK: {
            if (inventory.type == NONE) {
                if (butStack.type == BURGER) {
                    if (IsKeyDown(KEY_LEFT_CONTROL)) {
                        // Ctrl: tira so o ingrediente do topo, nao o hamburguer inteiro
                        Ingredient aux;
                        stack_pop(butStack, aux);
                        stack_push(inventory, aux);

                        break;
                    }

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
