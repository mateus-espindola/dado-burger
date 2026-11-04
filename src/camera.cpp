#include <math.h>

#include "../include/camera.hpp"

void setCamera(Match& match){
    
    match.camera = { 0 };

    match.camera.target = { match.player.object.pos.x, match.player.object.pos.y};
    match.camera.offset = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - PLAYER_START_POS.y / 2.0f };
    match.camera.zoom = 0.8f;

}

// void cameraProcess(Match& match){
    
//     float t = 1.0f - expf(-8.0f * GetFrameTime());

//     match.camera.target.x += (match.player.object.pos.x - match.camera.target.x) * t;
//     match.camera.target.y += (match.player.object.pos.y - match.camera.target.y) * t;
// }

void cameraProcess(Camera2D& camera, Player& player, Sprite background) {
    Vector2 targetPos = { player.object.pos.x, player.object.pos.y};

     float cameraInterpolation = 1.0f - expf(-8.0f * GetFrameTime());
    camera.target.x += (targetPos.x - camera.target.x) * cameraInterpolation;

    if (camera.target.x < camera.offset.x) {
        camera.target.x = camera.offset.x;
    }
    if (camera.target.x > background.width * GAME_SCALE - camera.offset.x) {
        camera.target.x = background.width * GAME_SCALE - camera.offset.x;
    }
}