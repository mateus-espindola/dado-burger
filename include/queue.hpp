#pragma once

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
};
