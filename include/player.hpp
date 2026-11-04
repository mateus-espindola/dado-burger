#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "food.hpp"
#include "tads.hpp"
#include "buttons.hpp"
#include "constants.hpp"
#include "sprites.hpp"

#include "raylib.h"




/* ============================ */
/*            OBJECT            */
/* ============================ */

struct Object {
    Sprite sprite;
    Vector2 pos;
    float radius;
};

enum Direction {
    DIR_LEFT,
    DIR_RIGHT
};




/* ============================ */
/*           PLAYER             */
/* ============================ */


struct PlayerInfo{
    char nome[50];
    int score;
};

struct Player {
    Object object;
    PlayerInfo info;
    Stack<Ingredient> inventory;
    Direction direction;
};

struct Slot {
    Button button;
    Stack<Ingredient> stack;
};


void setPlayer(Player&);

void playerProcess(Player& player, Sprite background);




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