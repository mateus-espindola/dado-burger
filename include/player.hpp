#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "food.hpp"
#include "tads.hpp"
#include "buttons.hpp"
#include "constants.hpp"
#include "sprites.hpp"
#include "match_enums.hpp"

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
    Object object;              //The constant bellow is defined in the struct WORLD in match.hpp
    Vector2 savedPos[WORLD_COUNT]; //Number of scenes that require camera2D. This is used to not lose the player position after each scene change
    PlayerInfo info;
    Stack inventory[INVENTORY_SLOTS];
    int selectedSlot;
    Direction direction;
};

// struct Slot {
//     Button button;
//     Stack<Ingredient> stack;
// };


void setPlayer(Player&);

void playerProcess(Player& player, float minX, float maxX);

// void playerProcessNoSprite(Player& player);




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
