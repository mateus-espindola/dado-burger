#include "match.hpp"
#include "camera.hpp"

void matchStart(Match& match) {

    setPlayer(match.player);

    setCamera(match);
}

void matchProcess(Match& match) {
    cameraUpdate(match);
    playerProcess(match.player);
}

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.pos.x -= 4;
}