#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include "constants.hpp"
#include "tads.hpp"

enum IngredientType{

    LETTUCE = 'a',
    BACON = 'b',
    ONION = 'c',
    KETCHUP = 'k',
    MUSTARD = 'm',
    MEAT = 'n',
    VEGAN_PROTEIN = 'v',
    FRIED_EGG = 'o',
    PICKLES = 'p',
    CHEDDAR = 'q',
    SWISS_CHEESE = 's',
    TOMATO = 't',
    UPPER_BREAD = 'z'

};

enum CookPoint {
    READY = -1,
    RAW = 0,
    RARE,
    MEDIUM_RARE,
    WELL_DONE,
    OVER_COOKED
};

struct CookState {
    bool cooking; //Indica se o ingrediente está cozinhando. Se sim ele nao diminui seu tempo ate estragar
    CookPoint cookPoint[2]; //Indica o quao cozido ele esta
    float cook_time; //Indica o tempo até mudar o estágio de cozimento
    
};

struct Ingredient {
    IngredientType type;
    CookState cook_state;
    int tempo_perecivel; // turnos ate estragar. -1 se nao estraga
};

enum CostumerType{

    CHILL_GUY,
    NORMAL,
    VEGAN,
    TONY

};



struct Costumer{
    int patience;
    List<Ingredient> order;
    CostumerType type;
};



#endif
