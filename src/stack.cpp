#include "../include/stack.hpp"

void stack_init(Stack& s) {
    s.top = nullptr;
    s.size = 0;
    s.type = NONE;
}

bool stack_empty(const Stack& s) {
    return s.top == nullptr;
}

void stack_push(Stack& s, const Ingredient& value) {
    bool wasEmpty = s.top == nullptr;

    s.top = new Stack_node{ s.top, value };
    s.size++;
}

bool stack_pop(Stack& s) {
    if (s.top == nullptr) return false;

    Stack_node *rem = s.top;
    s.top = rem->below;
    delete rem;

    s.size--;

    return true;
}

bool stack_pop(Stack& s, Ingredient& out) {
    if (s.top == nullptr) return false;
    out = s.top->data;
    return stack_pop(s);
}

bool stack_top(const Stack& s, Ingredient& out) {
    if (stack_empty(s)) return false;
    out = s.top->data;
    return true;
}

size_t stack_size(const Stack& s) {
    size_t n = 0;
    for (Stack_node *p = s.top; p != nullptr; p = p->below) n++;
    return n;
}

void stack_destroy(Stack& s) {
    while (!stack_empty(s)) {
        stack_pop(s); // Usa a versão que apenas remove e deleta o nó
    }
}
