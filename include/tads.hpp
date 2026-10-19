#ifndef TADS_HPP
#define TADS_HPP

// ---------- Pilha ----------
template<typename T>
struct Stack_node {
    Stack_node<T> *below;
    T data;
};

template<typename T>
struct Stack {
    Stack_node<T> *top;
}; // The Hamburguer struct is a stack of ingredients

// ---------- Fila ----------
template<typename T>
struct Queue_node {
    Queue_node<T> *prox; // The one who comes after him in line
    T data;
};

template<typename T>
struct Queue {
    Queue_node<T> *first;
    Queue_node<T> *last;
};

// ---------- AVL ----------
template<typename T>
struct AVL_node {
    T data;
    AVL_node<T> *right;
    AVL_node<T> *left;
};

template<typename T>
struct AVL {
    AVL_node<T> *root;
};

// ---------- Lista ----------
template<typename T>
struct List_node {
    List_node<T> *prox;
    T data;
};

template<typename T>
struct List {
    List_node<T> *start;
}; // The Recipe struct is a list of ingredients

#endif