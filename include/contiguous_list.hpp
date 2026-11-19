#pragma once
#include <stdlib.h>

constexpr int CONTIGUOUS_LIST_INITIAL_CAPACITY = 32;

template<typename T>
struct ContiguousList {
    T* data;
    int size;
    int capacity;
};

template<typename T>
void initializeContiguousList(ContiguousList<T>& list, const int& capacity) {
    list.size = 0;
    list.capacity = capacity;
    list.data = static_cast<T*>(malloc(capacity * sizeof(T)));
}

template<typename T>
bool insertContiguousList(ContiguousList<T>& list, T newElement, int pos) {
    if (list.size == list.capacity) return false;
    if (pos > list.size || pos < 0) return false;

    for (int i = list.size; i>pos; i--) {
        list.data[i] = list.data[i-1];
    }

    list.data[pos] = newElement;
    list.size++;
}
