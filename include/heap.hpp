#pragma once

#include <iostream>
#include "food.hpp"

constexpr int INITIAL_HEAP_CAPACITY = 32;

template <typename T>
struct Heap {
    T *data;
    int size;
    int capacity;
    IngredientType type;
};

// AUX FUNCTIONS
template <typename T>
void swap(T& a, T& b) {
    T aux = a;
    a = b;
    b = aux;
}

inline int left_child(int i) {
    return 2 * i + 1;
}

inline int right_child(int i) {
    return 2 * i + 2;
}

inline int father(int i) {
    return (i - 1) / 2;
}

template <typename T>
void heapify(Heap<T>& heap, int i) {
    int smallest = i;
    int l_child = left_child(i);
    int r_child = right_child(i);

    if (l_child < heap.size && heap.data[smallest] > heap.data[l_child]) {
        smallest = l_child;
    }

    if (r_child < heap.size && heap.data[smallest] > heap.data[r_child]) {
        smallest = r_child;
    }

    if (smallest != i) {
        swap(heap.data[i], heap.data[smallest]);
        heapify(heap, smallest);
    }
}

// MAIN FUNCTIONS
template <typename T>
void initializeHeap(Heap<T>& heap) {
    heap.capacity = INITIAL_HEAP_CAPACITY;
    heap.size = 0;
    heap.data = new T[heap.capacity];
    heap.type = NONE;
}

// drawHeap()

template <typename T>
int insertHeap(Heap<T>& heap, T value) {
    if (heap.size == heap.capacity) {
        std::cout << "You cannot insert more items on this heap\n";
        return 0;
    }

    bool wasEmpty = heap.size == 0;

    heap.size++;
    int i = heap.size - 1;
    heap.data[i] = value;

    while (i != 0 && heap.data[i] < heap.data[father(i)]) {
        swap(heap.data[i], heap.data[father(i)]);
        i = father(i);
    }

    // So define o tipo do heap a partir do ingrediente se ele estava vazio,
    // igual ao stack_push: evita que o tipo do heap mude a cada insercao.
    if (wasEmpty) heap.type = value.type;

    return 67;
}

// Olha o menor valor sem remover. Retorna false se vazio
template <typename T>
bool peekMinHeap(const Heap<T>& heap, T& out) {
    if (heap.size == 0) return false;
    out = heap.data[0];
    return true;
}

template <typename T>
T getMinValueHeap(Heap<T>& heap) {
    if (heap.size == 0) {
        return T();
    }

    if (heap.size == 1) {
        heap.size--;
        heap.type = NONE;
        return heap.data[0];
    }

    T min = heap.data[0];
    heap.data[0] = heap.data[heap.size - 1];
    heap.size--;
    heapify(heap, 0);

    return min;
}

// Remove o elemento no indice idx (nao precisa ser a raiz) preservando a propriedade de heap.
// Troca pelo ultimo elemento, encolhe o size e sobe/desce esse elemento pro lugar certo.
template <typename T>
void removeAt(Heap<T>& heap, int idx) {
    if (idx < 0 || idx >= heap.size) return;

    heap.size--;

    if (idx == heap.size) {
        if (heap.size == 0) heap.type = NONE;
        return; // era o ultimo, so cortar
    }

    heap.data[idx] = heap.data[heap.size];

    while (idx != 0 && heap.data[idx] < heap.data[father(idx)]) {
        swap(heap.data[idx], heap.data[father(idx)]);
        idx = father(idx);
    }
    heapify(heap, idx);

    if (heap.size == 0) heap.type = NONE;
}

template <typename T>
void exterminateHeap(Heap<T>& heap) {
    delete[] heap.data;
    heap.data = nullptr;
    heap.size = 0;
    heap.capacity = 0;
}