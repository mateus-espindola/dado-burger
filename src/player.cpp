#include "player.hpp"

void setPlayer(Player& player){

    player.savedPos[WORLD_KITCHEN] = PLAYER_KITCHEN_POS;
    player.savedPos[WORLD_OVEN] = PLAYER_OVEN_POS;

    player.object.pos = player.savedPos[WORLD_KITCHEN];
    player.direction = DIR_RIGHT;

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