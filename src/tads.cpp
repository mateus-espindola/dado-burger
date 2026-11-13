#include "../include/tads.hpp"

//STACK

// Inicializa a pilha vazia (chame sempre ao criar)
void stack_init(Stack& s) {
    s.top = nullptr;
    s.size = 0;
    s.type = NONE;
}

bool stack_empty(const Stack& s) {
    return s.top == nullptr;
}

// Empilha no topo: O(1)
void stack_push(Stack& s, const Ingredient& value) {
    s.top = new Stack_node{ s.top, value };
    s.size++;
    s.type = value.type;
}

// Desempilha o topo. Retorna false se vazia: O(1)
bool stack_pop(Stack& s) {
    if (s.top == nullptr) return false;

    Stack_node *rem = s.top;
    s.top = rem->below;
    delete rem;

    s.size--;
    s.type = (s.top != nullptr) ? s.top->data.type : NONE;
    return true;
}

bool stack_pop(Stack& s, Ingredient& out) {
    if (s.top == nullptr) return false;
    out = s.top->data;
    return stack_pop(s);
}

// Retorna o elemento do topo sem desempilhar. Retorna false se vazia
bool stack_top(const Stack& s, Ingredient& out) {
    if (stack_empty(s)) return false;
    out = s.top->data;
    return true;
}

// Quantidade de elementos: O(n)
size_t stack_size(const Stack& s) {
    size_t n = 0;
    for (Stack_node *p = s.top; p != nullptr; p = p->below) n++;
    return n;
}

// Destroi a pilha liberando todos os nós alocados dinamicamente
void stack_destroy(Stack& s) {
    while (!stack_empty(s)) {
        stack_pop(s); // Usa a versão que apenas remove e deleta o nó
    }
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





// LIST
