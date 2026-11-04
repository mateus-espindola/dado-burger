#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "food.hpp"
#include "food.hpp"
#include "tads.hpp"
#include "buttons.hpp"

#include "raylib.h"




/* ============================ */
/*           PLAYER             */
/* ============================ */


struct PlayerInfo{
    char nome[50];
    int score;
};

struct Player {
    PlayerInfo info;
    Stack<Ingredient> inventory;
    Vector2 pos;
};

struct Slot {
    Button button;
    Stack<Ingredient> stack;
};


void setPlayer(Player&);




/* ============================ */
/*          COSTUMERS           */
/* ============================ */

enum CostumerType{

    CHILL_GUY,
    NORMAL,
    VEGAN,
    TONY

};

struct Costumer{
    int patience;
    List<Ingredient> order;
    CostumerType type;
};

#endif