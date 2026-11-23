#include <algorithm>

#include "../include/food.hpp"
#include "../include/match.hpp"
//#include "game.hpp"


IngredientType charToIngType(char c) {
    switch (c) {
        case 'L': return LETTUCE;
        case 'a': return LETTUCE;
        case 'B': return BACON;
        case 'b': return BACON;
        case 'O': return ONION;
        case 'c': return ONION;
        case 'K': return KETCHUP;
        case 'k': return KETCHUP;
        case 'm': return MUSTARD;
        case 'M': return MEAT;
        case 'n': return MEAT;
        case 'E': return EGG;
        case 'o': return EGG;
        case 'P': return PICKLES;
        case 'p': return PICKLES;
        case 'C': return CHEDDAR;
        case 'q': return CHEDDAR;
        case 'S': return SWISS_CHEESE;
        case 's': return SWISS_CHEESE;
        case 'T': return TOMATO;
        case 't': return TOMATO;
        case 'U': return UPPER_BREAD;
        case 'z': return UPPER_BREAD;
        case 'D': return LOWER_BREAD;
        case 'y': return LOWER_BREAD;
        default:  return NONE;   // inclui '0' e qualquer letra desconhecida
    }
}

// turnos até estragar; -1 = não estraga
int perishTimeOf(IngredientType type) {
    switch (type) {
        case MEAT:
        case BACON:
        case EGG:
            return COOKABLE_PERISH_TIME;
        default:
            return -1;
    }
}

CookPoint cookingStateOf(IngredientType type) {
    switch (type) {
        case TOMATO:
        case SWISS_CHEESE:
        case CHEDDAR:
        case LETTUCE:
        case ONION: return NEEDS_TO_CUT;
        case MEAT:
        case BACON:
        case EGG:     return RAW;
        default:      return READY;
    }
}

CookPoint practicalCookingStateOf(Ingredient ing) {
    if (ing.cook_state.cookInfo[0].cookPoint == OVER_COOKED || ing.cook_state.cookInfo[1].cookPoint == OVER_COOKED) {
        return OVER_COOKED;
    }

    return (CookPoint) std::min(ing.cook_state.cookInfo[0].cookPoint, ing.cook_state.cookInfo[1].cookPoint);
}

float cookTimeOf(IngredientType type) {
    switch (type) {
        default:      return FPS * 14; //Time in seconds to cook
        // default: return COOK_TIME;
    }
}


// Inicializa um ingrediente recém-criado (estoque infinito, ainda cru)
void initIngredient(Ingredient &ing, char ingType) {

    IngredientType type = charToIngType(ingType);

    ing.type = type;

    ing.cook_state.cooking      = false;
    ing.cook_state.cookInfo[0].cookPoint = cookingStateOf(type);
    ing.cook_state.cookInfo[1].cookPoint = cookingStateOf(type);
    ing.cook_state.cookInfo[0].cook_time = cookTimeOf(type);
    ing.cook_state.cookInfo[1].cook_time = cookTimeOf(type);

    ing.perish_time = perishTimeOf(type);
}


void cutIngredient(Ingredient& ing /*, Stack& ready_ing*/){
    ing.cook_state.cookInfo[0].cookPoint = READY;
    ing.cook_state.cookInfo[1].cookPoint = READY;

    /*
    Stack_node *node = new Stack_node;

    node->data = ing;
    node->below = ready_ing.top;
    ready_ing.top = node;
    */
}

void flipMeat(Ingredient& ing){
    CookInfo aux = ing.cook_state.cookInfo[1];
    ing.cook_state.cookInfo[1] = ing.cook_state.cookInfo[0];
    ing.cook_state.cookInfo[0] = aux;
    // std::swap(ing.cook_state.cookInfo[0], ing.cook_state.cookInfo[1]);
}


void cookDefault(Ingredient& ing){

    if(ing.cook_state.cookInfo[0].cook_time > 0 || ing.cook_state.cookInfo[1].cook_time > 0){
        ing.cook_state.cookInfo[0].cook_time -= COOK_SPEED;
        ing.cook_state.cookInfo[1].cook_time -= COOK_SPEED;
    }
    else{
        if(ing.cook_state.cookInfo[0].cookPoint == RAW || ing.cook_state.cookInfo[1].cookPoint == RAW){
            ing.cook_state.cookInfo[0].cookPoint = READY;
            ing.cook_state.cookInfo[1].cookPoint = READY;
        }
        else{
            ing.cook_state.cookInfo[0].cookPoint = OVER_COOKED;
            ing.cook_state.cookInfo[1].cookPoint = OVER_COOKED;
        }
        ing.cook_state.cookInfo[0].cook_time = cookTimeOf(ing.type);
        ing.cook_state.cookInfo[1].cook_time = cookTimeOf(ing.type);
    }

}

//E ALGUMA MALUQUICE QUE DEIXA DAR ++ NOS ENUM. E TIPO DEFINIR UMA OPERACAO NOVA
//NOTA: O ++ TEM QUE SER ANTES POR ALGUM MOTIVO
CookPoint& operator++(CookPoint& c) {
    if (c != READY && c < OVER_COOKED)
        c = static_cast<CookPoint>(c + 1);
    return c;
}

void cookMeat(Ingredient& ing){

    if(ing.cook_state.cookInfo[0].cook_time > 0)
        ing.cook_state.cookInfo[0].cook_time -= (COOK_SPEED + MEAT_EXTRA_COOK_SPEED);
    else{
        ++ing.cook_state.cookInfo[0].cookPoint;
        ing.cook_state.cookInfo[0].cook_time = cookTimeOf(ing.type);
    }

}


void cookAll(ButtonVec *butonVec) {
    for (int i = 0; i < STATE_QUANTITY; i++) {
        ButtonVec& screen = butonVec[i];
        if (screen.buttons == nullptr) continue;

        for (int j = 0; j < screen.size; j++) {
            Button& b = screen.buttons[j];

            if (b.type != INSERT) continue;
            if (b.target.size <= 0) continue;   // top é inválido com a pilha vazia

            Ingredient& ing = b.target.top->data;

            if(ing.cook_state.cookInfo[0].cookPoint == OVER_COOKED ||
                ing.cook_state.cookInfo[1].cookPoint == OVER_COOKED) continue;

            switch(b.target.type){
                case MEAT:
                    cookMeat(ing);
                break;
                case EGG:
                case BACON:
                    cookDefault(ing);
                break;
                default: break;
            }
        }
    }
}

// Decai o perish_time de todo ingrediente guardado em HEAP/READIES_HEAP.
// perish_time == -1 significa que o ingrediente nao estraga.
void processRottingIngredients(ButtonVec *buttonsVec) {
    for (int i = 0; i < STATE_QUANTITY; i++) {
        ButtonVec& screen = buttonsVec[i];
        if (screen.buttons == nullptr) continue;

        for (int j = 0; j < screen.size; j++) {
            Button& b = screen.buttons[j];

            if (b.type != HEAP && b.type != READIES_HEAP) continue;

            // removeAt troca pelo ultimo elemento e reencaixa no lugar, entao o item
            // que cai em k pode ser outro ainda nao conferido: nao avanca k nesse caso
            int k = 0;
            while (k < b.heap.size) {
                Ingredient& ing = b.heap.data[k];

                if (ing.perish_time > 0) ing.perish_time -= INGREDIENT_DECAY_RATE;

                if (ing.perish_time == 0 && perishTimeOf(ing.type) > 0) {
                    removeAt(b.heap, k);
                    continue;
                }

                k++;
            }
        }
    }
}


// Devolve a porcentagem de semelhança entre o burger e o pedido
float compare_hamburger_with_order(Stack& hamburger, LinkedList<Ingredient>& order){
    float desiredScore = 2*lengthLinkedList(order);
    if (desiredScore == 0) return 0; // pedido vazio: nao ha o que comparar

    float currentScore = 0;

    Ingredient auxIng;
    LinkedList_node<Ingredient>* auxPtr = order.start;
    while (stack_pop(hamburger, auxIng)) {
        if (auxPtr == nullptr) break;

        if (auxIng.type == auxPtr->data.type) currentScore++;
        if (practicalCookingStateOf(auxIng) == practicalCookingStateOf(auxPtr->data)) currentScore++;

        auxPtr = auxPtr->prox;
    }

    return currentScore / desiredScore;
}
