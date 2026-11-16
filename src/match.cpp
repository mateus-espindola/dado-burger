#include "../include/match.hpp"
#include "../include/camera.hpp"

void matchStart(Match& match) {
    initializeQueue(match.costumer_line);

    match.screen = KITCHEN;

    setPlayer(match.player);

    setKitchenCamera(match);
}

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.object.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.object.pos.x -= 4;
}
