#include "../include/tads.hpp"

//STACK

template <typename T>
Stack<T> *stack_create() {
    Stack<T> *s = new Stack<T>;
    s->top = nullptr;
    return s;
}

template <typename T>
bool stack_is_empty(const Stack<T> *s) {
    return s->top == nullptr;
}

template <typename T>
void stack_push(Stack<T> *s, T data) {
    Stack_node<T> *n = new Stack_node<T>;
    n->data = data;
    n->below = s->top;   // o novo nó aponta para o antigo topo
    s->top = n;
}

template <typename T>
bool stack_pop(Stack<T> *s, T *out) {
    if (stack_is_empty(s)) return false;

    Stack_node<T> *n = s->top;
    if (out != nullptr) *out = n->data;
    s->top = n->below;
    delete n;
    return true;
}

template <typename T>
bool stack_top(const Stack<T> *s, T *out) {
    if (stack_is_empty(s)) return false;
    *out = s->top->data;
    return true;
}

template <typename T>
int stack_size(const Stack<T> *s) {
    int size = 0;
    for (Stack_node<T> *aux = s->top; aux != nullptr; aux = aux->below)
        size++;
    return size;
}

template <typename T>
void stack_destroy(Stack<T> *s) {
    while (!stack_is_empty(s)) stack_pop(s, nullptr);
    delete s;
}




//QUEUE

template <typename T>
Queue<T> *queue_create() {
    Queue<T> *q = new Queue<T>;
    q->first = nullptr;
    q->last = nullptr;
    return q;
}

template <typename T>
bool queue_is_empty(const Queue<T> *q) {
    return q->first == nullptr;
}

template <typename T>
void queue_enqueue(Queue<T> *q, T data) {
    Queue_node<T> *n = new Queue_node<T>;
    n->data = data;
    n->prox = nullptr;

    if (queue_is_empty(q)) {
        q->first = n;          // fila vazia: o nó é o primeiro e o último
    } else {
        q->last->prox = n;     // o último atual passa a apontar para o novo
    }
    q->last = n;
}

template <typename T>
bool queue_dequeue(Queue<T> *q, T *out) {
    if (queue_is_empty(q)) return false;

    Queue_node<T> *n = q->first;
    if (out != nullptr) *out = n->data;
    q->first = n->prox;
    if (q->first == nullptr) q->last = nullptr;  // esvaziou: zera o last também
    delete n;
    return true;
}

template <typename T>
bool queue_front(const Queue<T> *q, T *out) {
    if (queue_is_empty(q)) return false;
    *out = q->first->data;
    return true;
}

template <typename T>
int queue_size(const Queue<T> *q) {
    int size = 0;
    for (Queue_node<T> *aux = q->first; aux != nullptr; aux = aux->prox)
        size++;
    return size;
}

template <typename T>
void queue_destroy(Queue<T> *q) {
    while (!queue_is_empty(q)) queue_dequeue(q, nullptr);
    delete q;
}