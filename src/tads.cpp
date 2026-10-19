#include "tads.hpp"

//STACK

Stack *stack_create() {
    Stack *s = new Stack;
    s->top = nullptr;
    return s;
}

bool stack_is_empty(const Stack *s) {
    return s->top == nullptr;
}

void stack_push(Stack *s, Ingredient ing) {
    Stack_node *n = new Stack_node;
    n->ing = ing;
    n->below = s->top;   // o novo nó aponta para o antigo topo
    s->top = n;
}

bool stack_pop(Stack *s, Ingredient *out) {
    if (stack_is_empty(s)) return false;

    Stack_node *n = s->top;
    if (out != nullptr) *out = n->ing;
    s->top = n->below;
    delete n;
    return true;
}

bool stack_top(const Stack *s, Ingredient *out) {
    if (stack_is_empty(s)) return false;
    *out = s->top->ing;
    return true;
}

int stack_size(const Stack *s) {
    int size = 0;
    for (Stack_node *aux = s->top; aux != nullptr; aux = aux->below)
        size++;
    return size;
}

void stack_destroy(Stack *s) {
    while (!stack_is_empty(s)) stack_pop(s, nullptr);
    delete s;
}




//QUEUE

Costumer_queue *queue_create() {
    Costumer_queue *q = new Costumer_queue;
    q->first = nullptr;
    q->last = nullptr;
    return q;
}

bool queue_is_empty(const Costumer_queue *q) {
    return q->first == nullptr;
}

void queue_enqueue(Costumer_queue *q, Costumer cost) {
    Queue_node *n = new Queue_node;
    n->cost = cost;
    n->prox = nullptr;

    if (queue_is_empty(q)) {
        q->first = n;          // fila vazia: o nó é o primeiro e o último
    } else {
        q->last->prox = n;     // o último atual passa a apontar para o novo
    }
    q->last = n;
}

bool queue_dequeue(Costumer_queue *q, Costumer *out) {
    if (queue_is_empty(q)) return false;

    Queue_node *n = q->first;
    if (out != nullptr) *out = n->cost;
    q->first = n->prox;
    if (q->first == nullptr) q->last = nullptr;  // esvaziou: zera o last também
    delete n;
    return true;
}

bool queue_front(const Costumer_queue *q, Costumer *out) {
    if (queue_is_empty(q)) return false;
    *out = q->first->cost;
    return true;
}

int queue_size(const Costumer_queue *q) {
    int size = 0;
    for (Queue_node *aux = q->first; aux != nullptr; aux = aux->prox)
        size++;
    return size;
}

void queue_destroy(Costumer_queue *q) {
    while (!queue_is_empty(q)) queue_dequeue(q, nullptr);
    delete q;
}