#include "../include/stack.hpp"

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
