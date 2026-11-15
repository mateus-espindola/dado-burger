#pragma once

#include "food.hpp"
#include <cstddef>

struct Stack_node {
    Stack_node *below;
    Ingredient data;
};

struct Stack {
    Stack_node *top;
    int capacity;
    int size;
    IngredientType type;
}; // The Hamburguer struct is a stack of ingredients

void stack_init(Stack& s);
bool stack_empty(const Stack& s);
void stack_push(Stack& s, const Ingredient& value);
bool stack_pop(Stack& s);
bool stack_pop(Stack& s, Ingredient& out);
bool stack_top(const Stack& s, Ingredient& out);
size_t stack_size(const Stack& s);
void stack_destroy(Stack& s);
