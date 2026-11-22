#pragma once

#include "player.hpp"
#include "tads.hpp"
#include "food.hpp"
#include "constants.hpp"
#include "raylib.h"

enum CostumerType{

    EMPTY = -1,
    CHILL_GUY = 0,
    NORMAL,
    VEGAN,
    TONY,
    COSTUMER_TYPES_QUANTITY

};

struct Costumer{
    float patience_time;
    LinkedList<Ingredient> order;
    CostumerType type;
    Object obj;
    float ideal_pos_x;
    bool leaving; // true quando ja foi atendido e esta saindo de tela pra esquerda
};

void getCostumerOrder(LinkedList<Ingredient>& list, const int order_cod, const AVL& avl, HashTable& ht);
void initializeCostumer(Costumer& cost, const AVL& avl, HashTable& ht);
void processCostumers(Queue<Costumer>& queue, Costumer counter[], const AVL& avl, HashTable& ht);
bool callCostumer(Queue<Costumer>& queue, Costumer counter[]);
std::string costumerOrderString(const Costumer& cost);
bool giveBurgerToCostumer(Costumer counter[], Player& player, Vector2 mouseWorld);
bool cheatGivePerfectBurger(Costumer counter[], Player& player, Vector2 mouseWorld);
float compare_hamburger_with_order(Stack& hamburger, LinkedList<Ingredient>& order);
