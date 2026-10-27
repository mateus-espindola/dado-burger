#ifndef TADS_HPP
#define TADS_HPP

#include <cstddef>

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

// Inicializa a lista vazia (chame sempre ao criar)
template<typename T>
void list_init(List<T>& l) {
    l.start = nullptr;
}

template<typename T>
bool list_empty(const List<T>& l) {
    return l.start == nullptr;
}

template<typename T>
size_t list_size(const List<T>& l) {
    size_t n = 0;
    for (List_node<T> *p = l.start; p != nullptr; p = p->prox) n++;
    return n;
}

// Insere no início: O(1)
template<typename T>
void push_front(List<T>& l, const T& value) {
    l.start = new List_node<T>{ l.start, value };
}

// Insere no fim: O(n), pois não há ponteiro para o último
template<typename T>
void push_back(List<T>& l, const T& value) {
    List_node<T> *novo = new List_node<T>{ nullptr, value };

    if (l.start == nullptr) {
        l.start = novo;
        return;
    }
    List_node<T> *p = l.start;
    while (p->prox != nullptr) p = p->prox;
    p->prox = novo;
}

// Insere na posição idx (0 = início). Retorna false se idx > tamanho
template<typename T>
bool insert_at(List<T>& l, size_t idx, const T& value) {
    if (idx == 0) {
        push_front(l, value);
        return true;
    }
    List_node<T> *p = l.start;
    for (size_t i = 0; i < idx - 1 && p != nullptr; i++) p = p->prox;
    if (p == nullptr) return false;

    p->prox = new List_node<T>{ p->prox, value };
    return true;
}

// Remove o primeiro elemento. Retorna false se vazia
template<typename T>
bool pop_front(List<T>& l) {
    if (l.start == nullptr) return false;
    List_node<T> *rem = l.start;
    l.start = rem->prox;
    delete rem;
    return true;
}

// Remove o último elemento. Retorna false se vazia
template<typename T>
bool pop_back(List<T>& l) {
    if (l.start == nullptr) return false;
    if (l.start->prox == nullptr) return pop_front(l);

    List_node<T> *p = l.start;
    while (p->prox->prox != nullptr) p = p->prox;
    delete p->prox;
    p->prox = nullptr;
    return true;
}

// Remove o elemento da posição idx. Retorna false se idx inválido
template<typename T>
bool remove_at(List<T>& l, size_t idx) {
    if (l.start == nullptr) return false;
    if (idx == 0) return pop_front(l);

    List_node<T> *p = l.start;
    for (size_t i = 0; i < idx - 1 && p->prox != nullptr; i++) p = p->prox;
    if (p->prox == nullptr) return false;

    List_node<T> *rem = p->prox;
    p->prox = rem->prox;
    delete rem;
    return true;
}

// Retorna ponteiro para o dado na posição idx, ou nullptr se não existir
template<typename T>
T* list_get(List<T>& l, size_t idx) {
    List_node<T> *p = l.start;
    for (size_t i = 0; i < idx && p != nullptr; i++) p = p->prox;
    return p ? &p->data : nullptr;
}

// Busca o primeiro elemento que satisfaz o predicado. Retorna ponteiro ou nullptr
template<typename T, typename Pred>
T* list_find(List<T>& l, Pred pred) {
    for (List_node<T> *p = l.start; p != nullptr; p = p->prox)
        if (pred(p->data)) return &p->data;
    return nullptr;
}

// Aplica uma função a cada elemento
template<typename T, typename Fn>
void list_for_each(List<T>& l, Fn fn) {
    for (List_node<T> *p = l.start; p != nullptr; p = p->prox) fn(p->data);
}

// Libera todos os nós e deixa a lista vazia
template<typename T>
void list_clear(List<T>& l) {
    while (l.start != nullptr) pop_front(l);
}

#endif