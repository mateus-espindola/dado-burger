#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include "constants.hpp"

enum IngredientType{

    LETTUCE = 'a',
    BACON = 'b',
    ONION = 'c',
    KETCHUP = 'k',
    MUSTARD = 'm',
    MEAT = 'n',
    FRIED_EGG = 'o',
    PICKLES = 'p',
    CHEDDAR = 'q',
    SWISS_CHEESE = 's',
    TOMATO = 't',
    UPPER_BREAD = 'z'

};

struct Ingredient{
    IngredientType type;
    int tempo_perecivel; // turnos ate estragar. -1 se nao estraga
};

struct AVL_node{
    int id;
    std::string recipe;
    AVL_node *right;
    AVL_node *left;
};

struct AVL{
    AVL_node *root;
};


struct List_node{
    List_node *prox;
    Ingredient ing;
};

struct Recipe{
    List_node *start;
}; // The Recipe struct is a list of ingredients

enum CostumerType{

    CHILL_GUY,
    NORMAL,
    VEGAN,
    TONY

};

struct Costumer{
    int patience;
    Recipe order;
    CostumerType type;
};

struct Stack_node{
   Stack_node *below;
   Ingredient ing;
};

struct Hamburger{
    Stack_node *top;
}; // The Hamburguer struct is a stack of ingredients


struct Queue_node{
    Queue_node *prox; //The one who comes after him in line
    Costumer cost;
};

struct Costumer_queue{
    Queue_node *first;
    Queue_node *last;
};

#endif
