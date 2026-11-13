#include "../include/match.hpp"
#include "../include/camera.hpp"

void matchStart(Match& match) {

    match.screen = KITCHEN;

    setPlayer(match.player);

    setKitchenCamera(match);
}

// void matchProcess(Match& match) {
//     cameraProcess(match);
//     playerProcess(match.player);
// }

// void matchProcess(Match& match, Sprite background, Vector2 mouse) {
//     // cameraProcess(match.camera, match.player, background);
//     cameraProcess(match.camera, match.player, match.spriteMatch[SPR_BACKGROUND].width * GAME_SCALE);
//     playerProcess(match.player, background);
// }

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.object.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.object.pos.x -= 4;
}
