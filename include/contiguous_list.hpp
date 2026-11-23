#pragma once
#include "constants.hpp"
#include "player.hpp"
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <algorithm>

constexpr int CONTIGUOUS_LIST_INITIAL_CAPACITY = 32;

// STRUCTS
template<typename T>
struct ContiguousList {
    T* data;
    int size;
    int capacity;
};


// AUX FUNCTIONS
template<typename PlayerInfo>
int partition(ContiguousList<PlayerInfo>& list, const int& ini, const int& end) {
    int pivot = list.data[end].score;
    int i = ini - 1;

    for (int j = ini; j < end; j++) {
        if (list.data[j].score > pivot) {
            i++;
            std::swap(list.data[i], list.data[j]);
        }
    }

    std::swap(list.data[i+1], list.data[end]);
    return i+1;
}

template<typename PlayerInfo>
void partitionSortRec(ContiguousList<PlayerInfo>& list, const int& ini, const int& end) {
    if (ini < end) {
        int mid = partition(list, ini, end);
        partitionSortRec(list, ini, mid-1);
        partitionSortRec(list, mid+1, end);
    }
}

template<typename T>
void initializeContiguousList(ContiguousList<T>& list, const int& capacity);

template<typename PlayerInfo>
void charCountingSort(ContiguousList<PlayerInfo>& list, const int& charIndex) {
    int n = list.size;

    ContiguousList<PlayerInfo> output;
    initializeContiguousList(output, n);

    int charRange = MAX_ASCII_CODE_SUPPORTED - MIN_ASCII_CODE_SUPPORTED;
    int count[charRange + 2]; // +1 para suportar o \0, +1 pq codigo vai de 0 a charRange+1
    memset(count, 0, sizeof(count));

    for (int i = 0; i < n; i++) {
        int charCode;

        if (charIndex < (int)list.data[i].nome.size()) { // Se o indice estiver dentro da string
            charCode = list.data[i].nome[charIndex] - (MIN_ASCII_CODE_SUPPORTED - 1);
        } else {
            charCode = 0;
        }

        count[charCode]++;
    }

    for (int i = 1; i <= charRange + 1; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n; i > 0; i--) {
        int idx = i-1;
        int charCode;

        if (charIndex < (int)list.data[idx].nome.size()) { // Se o indice estiver dentro da string
            charCode = list.data[idx].nome[charIndex] - (MIN_ASCII_CODE_SUPPORTED - 1);
        } else {
            charCode = 0;
        }

        output.data[count[charCode]-1] = list.data[idx];
        count[charCode]--;
    }

    for (int i = 0; i < n; i++) {
        list.data[i] = output.data[i];
    }

    delete[] output.data;
}


// MAIN FUNCTIONS
template<typename T>
void initializeContiguousList(ContiguousList<T>& list, const int& capacity) {
    list.size = 0;
    list.capacity = capacity;
    list.data = new T[capacity];
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
    return true;
}

template<typename PlayerInfo>
void partitionSort(ContiguousList<PlayerInfo>& list) {
    int ini = 0;
    int end = list.size - 1;
    partitionSortRec(list, ini, end);
}

template<typename PlayerInfo>
void stringRadixSort(ContiguousList<PlayerInfo>& list) {
    int maxLen = 0;
    for (int i = 0; i < list.size; i++) {
        if (maxLen < (int)list.data[i].nome.size()) {
            maxLen = (int)list.data[i].nome.size();
        }
    }

    for (int pos = maxLen; pos > 0; pos--) {
            charCountingSort(list, pos - 1);
        }
}
