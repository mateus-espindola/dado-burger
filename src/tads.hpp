#include "data_structures.hpp"

struct Stack_node{
   Stack_node *below;
   Ingredient ing;
};

struct Stack{
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