#include "data_structures.hpp"

template<typename T>
struct Stack_node{
   Stack_node *below;
   T data;
};

struct Stack{
    Stack_node *top;
}; // The Hamburguer struct is a stack of ingredients

template<typename T>
struct Queue_node{
    Queue_node *prox; //The one who comes after him in line
    T data;
};

struct Queue{
    Queue_node *first;
    Queue_node *last;
};

template<typename T>
struct AVL_node{
    T data;
    AVL_node *right;
    AVL_node *left;
};

struct AVL{
    AVL_node *root;
};

template<typename T>
struct List_node{
    List_node *prox;
    T data;
};