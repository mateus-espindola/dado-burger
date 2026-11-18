#pragma once

#include "player.hpp"
#include "tads.hpp"
#include "food.hpp"
#include "constants.hpp"
#include "raylib.h"

enum CostumerType{

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
};

void getCostumerOrder(LinkedList<Ingredient>& list, const int order_cod, const AVL& avl, const HashTable& ht);
void initializeCostumer(Costumer& cost);
void processCostumers(Queue<Costumer>& queue, const AVL& avl, const HashTable& ht);
