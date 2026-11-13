#include <cstring>

// #include "food.hpp"
#include "../include/player.hpp"

// void setPlayer(Player& player){

//     player.savedPos[WORLD_KITCHEN] = PLAYER_KITCHEN_POS;
//     player.savedPos[WORLD_OVEN] = PLAYER_OVEN_POS;

//     player.object.pos = player.savedPos[WORLD_KITCHEN];
//     player.direction = DIR_RIGHT;

//     memset(player.inventory, 0, sizeof(player.inventory));

//     stack_init(player.inventory[0].items);
//     stack_init(player.inventory[1].items);
//     stack_init(player.inventory[2].items);

//     player.inventory->items.top->data.type = LETTUCE;

// }

void setPlayer(Player& player) {

    player.savedPos[WORLD_KITCHEN] = PLAYER_KITCHEN_POS;
    player.savedPos[WORLD_OVEN] = PLAYER_OVEN_POS;

    player.object.pos = player.savedPos[WORLD_KITCHEN];
    player.direction = DIR_RIGHT;

    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        stack_init(player.inventory[i].items);

        player.inventory[i].count = 0;
        player.inventory[i].capacity = 1; // Exemplo
        player.inventory[i].type = NONE;
    }

    // Ingredient ing;
    // initIngredient(ing, LETTUCE);

    // stack_push(player.inventory[0].items, ing);

    // player.inventory[0].count = 1;
    // player.inventory[0].type = LETTUCE;
}

void playerProcess(Player& player, float minX, float maxX) {
    int playerSpeed = IsKeyDown(KEY_LEFT_SHIFT) ? PLAYER_SPEED * 2 : PLAYER_SPEED;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player.direction = DIR_RIGHT;
        player.object.pos.x += playerSpeed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player.direction = DIR_LEFT;
        player.object.pos.x -= playerSpeed;
    }

    if (player.object.pos.x < minX) player.object.pos.x = minX;
    if (player.object.pos.x > maxX) player.object.pos.x = maxX;
}

// void playerProcessNoSprite(Player& player){

//     int playerSpeed;
//     if (IsKeyDown(KEY_LEFT_SHIFT)) {
//         playerSpeed = PLAYER_SPEED * 2;
//     } else {
//         playerSpeed = PLAYER_SPEED;
//     }

//     if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
//         player.direction = DIR_RIGHT;
//         player.object.pos.x += playerSpeed;
//     }
//     if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
//         player.direction = DIR_LEFT;
//         player.object.pos.x -= playerSpeed;
//     }
// }
