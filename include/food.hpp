#pragma once

#include "linked_list.hpp"

/* ============================ */
/*          INGREDIENT         */
/* ============================ */

enum IngredientType{

    NONE = '0',
    LETTUCE = 'a',
    BACON = 'b',
    ONION = 'c',
    KETCHUP = 'k',
    MUSTARD = 'm',
    MEAT = 'n',
    VEGAN_PROTEIN = 'v',
    EGG = 'o',
    PICKLES = 'p',
    CHEDDAR = 'q',
    SWISS_CHEESE = 's',
    TOMATO = 't',
    UPPER_BREAD = 'z',
    LOWER_BREAD = 'y',
    BURGER = 'x'

};

enum CookPoint {
    NEEDS_TO_CUT = -2,
    READY = -1,
    RAW = 0,
    RARE,
    MEDIUM_RARE,
    WELL_DONE,
    OVER_COOKED
};

struct CookInfo{
    CookPoint cookPoint; //Indica o quao cozido ele esta
    float cook_time; //Indica o tempo até mudar o estágio de cozimento
};

struct CookState {
    bool cooking; //Indica se o ingrediente está cozinhando. Se sim ele nao diminui seu tempo ate estragar
    CookInfo cookInfo[2];
};

struct Ingredient {
    IngredientType type;
    CookState cook_state;
    int perish_time; // turnos ate estragar. -1 se nao estraga

    bool operator<(const Ingredient& other) const {
        return this->perish_time < other.perish_time;
    } // É TIPO AQUELE BAGULHO QUE TU FEZ DO operator++ QUE DÁ PRA DEFINIR O OPERADOR
      // FIZ ISSO PRA PODER COMPARAR OS INGREDIENTES EM RELAÇÃO AO TEMPO DE ESTRAGAR, PRA PODER USAR O HEAP E TER O INGREDIENTE QUE VAI ESTRAGAR PRIMEIRO NO TOPO

    bool operator>(const Ingredient& other) const {
        return this->perish_time > other.perish_time;
    }
};

// //This is necessary so that the player can hold a burger. The player inventory doesen't comport stacks, but it comports a type
// struct hamburger {
//     Stack<Ingredient> hamburger;
// };

void initIngredient(Ingredient &ing, char ingType);
struct ButtonVec; //Declaracao antecipada
void cookAll(ButtonVec *butonVec);
float cookTimeOf(IngredientType type);
void cutIngredient(Ingredient& ing /*, Stack& ready_ing*/);
void flipMeat(Ingredient& ing);
