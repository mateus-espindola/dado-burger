#pragma once

#include "constants.hpp"
#include <iostream>

template<typename T>
struct Queue_node {
    Queue_node<T> *prox; // The one who comes after him in line
    T data;
};

template<typename T>
struct Queue {
    Queue_node<T> *first;
    Queue_node<T> *last;
    int size;

    int costumers_generated;
    float costumer_timer; // We did the queue generic but realistically it's worth it to store costumer-related information
};

template <typename T>
void initializeQueue(Queue<T>& queue) {
    queue.first = nullptr;
    queue.last = nullptr;
    queue.size = 0;
    queue.costumers_generated = 0;
    queue.costumer_timer = COSTUMER_TIMER_MAX;
    return;
}

template <typename T>
bool isEmptyQueue(const Queue<T>& queue) {
    return queue.first == nullptr;
}

template <typename T>
void enqueue(Queue<T>& queue, T data) {
    Queue_node<T> *newNode = new Queue_node<T>;
    newNode->data = data;
    newNode->prox = nullptr;

    if (isEmptyQueue(queue)) {
        queue.first = newNode;          // fila vazia: o nó é o primeiro e o último
    } else {
        queue.last->prox = newNode;     // o último atual passa a apontar para o novo
    }
    queue.last = newNode;

    queue.size++;
}

template <typename T>
bool dequeue(Queue<T>& queue, T *out) {
    if (isEmptyQueue(queue)) return false;

    Queue_node<T> *aux = queue.first;
    if (out != nullptr) *out = aux->data;
    queue.first = aux->prox;
    if (queue.first == nullptr) queue.last = nullptr;  // esvaziou: zera o last também
    delete aux;

    queue.size--;

    return true;
}

template <typename T>
bool getFrontElementQueue(const Queue<T>& queue, T *out) {
    if (isEmptyQueue(queue)) return false;
    *out = queue.first->data;
    return true;
}

template <typename T>
int lengthQueue(const Queue<T>& queue) {
    int size = 0;
    for (Queue_node<T> *aux = queue.first; aux != nullptr; aux = aux->prox)
        size++;
    return size;
}

template <typename T>
void exterminateQueue(Queue<T>& queue) {
    while (!isEmptyQueue(queue)) dequeue(queue, (T*)nullptr);
}
