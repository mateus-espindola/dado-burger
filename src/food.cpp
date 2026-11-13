#include "../include/food.hpp"
#include "../include/match.hpp"
//#include "game.hpp"

// int findClick(MouseInput &mouse, Button *button_vec/*jeito de passar vetor*/, int size){

//     //A funcao recebe a coordenada do click e um vetor [x + 1]
//     //PRECISO DE UMA OPINIAO: A posicao inicial do vetor pode indicar quantos elementos tem no vetor, que que tu acha? Ou a gente passa de parametro o tamanho por constantes?
//     //dos botoes do comodo onde x e a quantidade de botoes desse comodo
//     //Ai tem um for que testa a colisao com todos os botoes
//     //e devolve o valor do indice do botao com o qual houve colisao

//     //for(int i = 1;  i < button_vec[0] + 1; i++){
//     for(int i = 0;  i < size; i++){
//         if (mouse.x >= button_vec[i].x1 && mouse.x <= button_vec[i].x2 &&
//             mouse.y >= button_vec[i].y1 && mouse.y <= button_vec[i].y2) {
//             return i;
//         }
//     }
//     return -1; // nenhum botão clicado
// }




//E ALGUMA MALUQUICE QUE DEIXA DAR ++ NOS ENUM. E TIPO DEFINIR UMA OPERACAO NOVA
//NOTA: O ++ TEM QUE SER ANTES POR ALGUM MOTIVO
CookPoint& operator++(CookPoint& c) {
    if (c != READY && c < OVER_COOKED)
        c = static_cast<CookPoint>(c + 1);
    return c;
}


IngredientType charToIngType(char c) {
    switch (c) {
        case 'a': return LETTUCE;
        case 'b': return BACON;
        case 'c': return ONION;
        case 'k': return KETCHUP;
        case 'm': return MUSTARD;
        case 'n': return MEAT;
        case 'v': return VEGAN_PROTEIN;
        case 'o': return EGG;
        case 'p': return PICKLES;
        case 'q': return CHEDDAR;
        case 's': return SWISS_CHEESE;
        case 't': return TOMATO;
        case 'z': return UPPER_BREAD;
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
        default:      return NEEDS_TO_CUT;
    }
}

float cookTimeOf(IngredientType type) {
    switch (type) {
        default:      return 0.0;
    }
}


// Inicializa um ingrediente recém-criado (estoque infinito, ainda cru)
void initIngredient(Ingredient &ing, char ingType) {

    IngredientType type = charToIngType(ingType);

    ing.type = type;

    ing.cook_state.cooking      = false;
    ing.cook_state.cookPoint[0] = cookingStateOf(type);
    ing.cook_state.cookPoint[1] = cookingStateOf(type);
    ing.cook_state.cook_time    = cookTimeOf(type);

    ing.perish_time = perishTimeOf(type);
}


void cut_ingredient(Ingredient& ing, Stack& ready_ing){
    ing.cook_state.cookPoint[1] = READY;

    Stack_node *node = new Stack_node;

    node->data = ing;
    node->below = ready_ing.top;
    ready_ing.top = node;
}




void cook_egg(Ingredient& ing, Stack& ready_ing){

    if(ing.cook_state.cook_time > 0)
        ing.cook_state.cook_time -= COOK_SPEED;
    else{
        ++ing.cook_state.cookPoint[1];
        ing.cook_state.cook_time = COOK_TIME;
    }

}




void cook_meat(Ingredient& ing, Stack& ready_ing){

    if(ing.cook_state.cook_time > 0)
        ing.cook_state.cook_time -= COOK_SPEED;
    else{
        ++ing.cook_state.cookPoint[1];
        ing.cook_state.cook_time = COOK_TIME;
    }

}

void flip_meat(Ingredient& ing){
    CookPoint aux = ing.cook_state.cookPoint[1];
    ing.cook_state.cookPoint[1] = ing.cook_state.cookPoint[0];
    ing.cook_state.cookPoint[0] = aux;
}

// void cook_cheese(){
//     return;
// }
//EU NAO LEMBRO O QUE MAIS TEM QUE COZINHAR TLG

void compare_hamburger_with_order(Stack *hamburger, List<Ingredient> *order){
    return;
}
