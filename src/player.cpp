#include "player.hpp"

void setPlayer(Player& player){

    player.object.pos = PLAYER_START_POS;
    player.direction = DIR_RIGHT;

}

void playerProcess(Player& player, Sprite background) {
    int playerSpeed;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        playerSpeed = PLAYER_SPEED * 2;
    } else {
        playerSpeed = PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player.direction = DIR_RIGHT;
        player.object.pos.x += playerSpeed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player.direction = DIR_LEFT;
        player.object.pos.x -= playerSpeed;
    }

    float minX = 0.0f + (player.object.sprite.width * GAME_SCALE) / 2;
    float maxX = background.width * GAME_SCALE - (player.object.sprite.width * GAME_SCALE) / 2;

    if (player.object.pos.x < minX) player.object.pos.x = minX;
    if (player.object.pos.x > maxX) player.object.pos.x = maxX;
}