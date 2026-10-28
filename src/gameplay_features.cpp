#include "raylib.h"
#include "../include/data_structures.hpp"
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




void cut_ingredient(Ingredient& ing, Stack<Ingredient>& ready_ing){
    ing.cook_state.cookPoint[1] = READY;
    
    Stack_node<Ingredient> *node = new Stack_node<Ingredient>;

    node->data = ing;
    node->below = ready_ing.top;
    ready_ing.top = node;
}




void cook_egg(Ingredient& ing, Stack<Ingredient>& ready_ing){

    if(ing.cook_state.cook_time > 0)
        ing.cook_state.cook_time -= COOK_SPEED;
    else{
        ++ing.cook_state.cookPoint[1];
        ing.cook_state.cook_time = COOK_TIME;
    }

}




void cook_meat(Ingredient& ing, Stack<Ingredient>& ready_ing){

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

void compare_hamburger_with_order(Stack<Ingredient> *hamburger, List<Ingredient> *order){
    return;
}