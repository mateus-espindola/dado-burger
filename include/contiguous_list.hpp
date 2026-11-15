#pragma once

constexpr int CONTIGUOUS_LIST_INITIAL_CAPACITY = 32;

template<typename T>
struct ContiguousList {
    T *data;
    int size;
    int capacity;
}
