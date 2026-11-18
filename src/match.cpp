#include "../include/match.hpp"
#include "../include/camera.hpp"

void matchStart(Match& match) {
    initializeQueue(match.costumer_line);
    for (int i = 0; i < COUNTER_SIZE; i++) {
        match.costumer_counter[i].type = EMPTY;
    }

    match.screen = KITCHEN;

    setPlayer(match.player);

    setKitchenCamera(match);
}

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.object.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.object.pos.x -= 4;
}
