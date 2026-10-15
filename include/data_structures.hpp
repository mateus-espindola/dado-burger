#include <iostream>

struct {

    int id;
    std::string recipe;
    AVL_node *right;
    AVL_node *left;


} AVL_node;

struct {

    AVL_node *root;

} Avl;


struct { 

    List_node *prox;
    Ingredient ing;

} List_node;

strcut {

    List_node *start;

} Recipe;


struct {

   Stack_node *below;
   Ingredient ing;

} Stack_node;

struct {

    Stack_node *topo;

} Hamburger;


struct {

    Queue_node *prox; //The one who comes after him in line
    Costumer cost;

} Queue_node;

struct {

    Queue_node *first;
    Queue_node *last;

} Costumer_queue;