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
        case 'V': return VEGAN_PROTEIN;
        case 'v': return VEGAN_PROTEIN;
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
        default:      return -1;
    }
}

CookPoint cookingStateOf(IngredientType type) {
    switch (type) {
        case TOMATO:
        case ONION: return NEEDS_TO_CUT;
        case MEAT:
        case VEGAN_PROTEIN:
        case BACON:
        case EGG:
        case SWISS_CHEESE:
        case CHEDDAR: return RAW;
        default:      return READY;
    }
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
        ing.cook_state.cookInfo[0].cook_time -= COOK_SPEED;
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
                case VEGAN_PROTEIN:
                    cookMeat(ing);
                break;
                case EGG:
                case BACON:
                case CHEDDAR:
                case SWISS_CHEESE:
                    cookDefault(ing);
                break;
                default: break;
            }
        }
    }
}



void compare_hamburger_with_order(Stack *hamburger, LinkedList<Ingredient> *order){
    return;
}
