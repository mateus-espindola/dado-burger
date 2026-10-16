#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <iostream>

struct AVL_node{
    int id;
    std::string recipe;
    AVL_node *right;
    AVL_node *left;
};

struct AVL{
    AVL_node *root;
};

template<typename T>
struct List_node{
    List_node<T> *prox;
    T data;
};

template<typename T>
struct List{
    List_node<T> *start;
}; // Generic singly linked list

template<typename T>
struct Stack_node{
   Stack_node<T> *below;
   T data;
};

template<typename T>
struct Stack{
    Stack_node<T> *top;
}; // Generic stack

template<typename T>
struct Queue_node{
    Queue_node<T> *prox; //The one who comes after him in line
    T data;
};

template<typename T>
struct Queue{
    Queue_node<T> *first;
    Queue_node<T> *last;
}; // Generic queue

#endif
