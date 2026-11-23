#include <cstring>

// #include "food.hpp"
#include "../include/player.hpp"


void setPlayer(Player& player) {

    player.savedPos[WORLD_KITCHEN] = PLAYER_KITCHEN_POS;
    player.savedPos[WORLD_OVEN] = PLAYER_OVEN_POS;

    player.object.pos = player.savedPos[WORLD_KITCHEN];
    player.direction = DIR_RIGHT;
    player.money = 0;

    player.moving = false;
    player.animFrame = 0;
    player.animTimer = 0.0f;

    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        stack_init(player.inventory[i]);

        player.inventory[i].size = 0;
        player.inventory[i].capacity = 1;
        player.inventory[i].type = NONE;
    }
}

void playerProcess(Player& player, float minX, float maxX) {
    int playerSpeed = IsKeyDown(KEY_LEFT_SHIFT) ? PLAYER_SPEED * 2 : PLAYER_SPEED;

    player.moving = false;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player.direction = DIR_RIGHT;
        player.object.pos.x += playerSpeed;
        player.moving = true;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player.direction = DIR_LEFT;
        player.object.pos.x -= playerSpeed;
        player.moving = true;
    }

    if (player.object.pos.x < minX) player.object.pos.x = minX;
    if (player.object.pos.x > maxX) player.object.pos.x = maxX;

    // Anima so enquanto anda; parado volta pro frame 0 (pose de pe)
    if (player.moving) {
        player.animTimer += GetFrameTime();
        if (player.animTimer >= PLAYER_ANIM_FRAME_TIME) {
            player.animTimer = 0.0f;
            player.animFrame = (player.animFrame + 1) % PLAYER_ANIM_FRAME_COUNT;
        }
    } else {
        player.animFrame = 0;
        player.animTimer = 0.0f;
    }
}
