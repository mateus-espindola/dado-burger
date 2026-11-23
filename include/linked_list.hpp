#pragma once

#include "queue.hpp"
#include <cstddef>

// ---------- Lista ----------
template<typename T>
struct LinkedList_node {
    LinkedList_node<T> *prox;
    T data;
};

template<typename T>
struct LinkedList {
    LinkedList_node<T> *start;
}; // The Recipe struct is a list of ingredients


// MAIN FUNCTIONS
template<typename T>
void initializeLinkedList(LinkedList<T>& l) {
    l.start = nullptr;
}

template<typename T>
bool isEmptyLinkedList(const LinkedList<T>& l) {
    return l.start == nullptr;
}

template<typename T>
int lengthLinkedList(const LinkedList<T>& l) {
    int n = 0;
    for (LinkedList_node<T> *p = l.start; p != nullptr; p = p->prox) n++;
    return n;
}

template<typename T>
void push_front(LinkedList<T>& l, const T& value) {
    l.start = new LinkedList_node<T>{ l.start, value };
}

template<typename T>
void push_back(LinkedList<T>& l, const T& value) {
    LinkedList_node<T> *novo = new LinkedList_node<T>{ nullptr, value };

    if (l.start == nullptr) {
        l.start = novo;
        return;
    }
    LinkedList_node<T> *p = l.start;
    while (p->prox != nullptr) p = p->prox;
    p->prox = novo;
}

template<typename T>
bool insert_at(LinkedList<T>& l, size_t idx, const T& value) {
    if (idx == 0) {
        push_front(l, value);
        return true;
    }
    LinkedList_node<T> *p = l.start;
    for (size_t i = 0; i < idx - 1 && p != nullptr; i++) p = p->prox;
    if (p == nullptr) return false;

    p->prox = new LinkedList_node<T>{ p->prox, value };
    return true;
}

template<typename T>
bool pop_front(LinkedList<T>& l) {
    if (l.start == nullptr) return false;
    LinkedList_node<T> *rem = l.start;
    l.start = rem->prox;
    delete rem;
    return true;
}

template<typename T>
bool pop_back(LinkedList<T>& l) {
    if (l.start == nullptr) return false;
    if (l.start->prox == nullptr) return pop_front(l);

    LinkedList_node<T> *p = l.start;
    while (p->prox->prox != nullptr) p = p->prox;
    delete p->prox;
    p->prox = nullptr;
    return true;
}

template<typename T>
bool remove_at(LinkedList<T>& l, size_t idx) {
    if (l.start == nullptr) return false;
    if (idx == 0) return pop_front(l);

    LinkedList_node<T> *p = l.start;
    for (size_t i = 0; i < idx - 1 && p->prox != nullptr; i++) p = p->prox;
    if (p->prox == nullptr) return false;

    LinkedList_node<T> *rem = p->prox;
    p->prox = rem->prox;
    delete rem;
    return true;
}

template<typename T>
T* list_get(LinkedList<T>& l, size_t idx) {
    LinkedList_node<T> *p = l.start;
    for (size_t i = 0; i < idx && p != nullptr; i++) p = p->prox;
    return p ? &p->data : nullptr;
}

template<typename T>
bool searchLinkedList(LinkedList<T>& l, const T& target, T& dst) {
    for (LinkedList_node<T> *p = l.start; p != nullptr; p = p->prox) {
        if (p->data == target) {
            dst = p->data;
            return true;
        }
    }
    return false;
}

template<typename T, typename Fn>
void list_for_each(LinkedList<T>& l, Fn fn) {
    for (LinkedList_node<T> *p = l.start; p != nullptr; p = p->prox) fn(p->data);
}

template<typename T>
void exterminateLinkedList(LinkedList<T>& l) {
    while (l.start != nullptr) pop_front(l);
}
