#include "match.hpp"
#include "camera.hpp"

void matchStart(Match& match) {

    setPlayer(match.player);

    setCamera(match);
}

// void matchProcess(Match& match) {
//     cameraProcess(match);
//     playerProcess(match.player);
// }

void matchProcess(Match& match, Sprite background) {
    // cameraProcess(match.camera, match.player, background);
    cameraProcess(match.camera, match.player, background);
    playerProcess(match.player, background);
}

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.object.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.object.pos.x -= 4;
}