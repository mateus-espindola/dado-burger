#include <math.h>
#include <cassert>

#include "../include/match_enums.hpp"
#include "../include/camera.hpp"
#include "../include/world.hpp"

void setKitchenCamera(Match& match){

    match.camera = { 0 };

    match.camera.target = { match.player.object.pos.x, match.player.object.pos.y};
    match.camera.offset = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - PLAYER_KITCHEN_POS.y / 2.0f };
    match.camera.zoom = 0.8f;

}

void setOvenCamera(Match& match){

    match.camera = { 0 };

    match.camera.offset = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
    match.camera.target = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
    match.camera.zoom   = 1.0f;

}

// void cameraProcess(Match& match){

//     float t = 1.0f - expf(-8.0f * GetFrameTime());

//     match.camera.target.x += (match.player.object.pos.x - match.camera.target.x) * t;
//     match.camera.target.y += (match.player.object.pos.y - match.camera.target.y) * t;
// }

// versão principal: recebe a largura do mundo
void cameraProcess(Camera2D& camera, const Player& player, float worldWidth) {
    float t = 1.0f - expf(-8.0f * GetFrameTime());
    camera.target.x += (player.object.pos.x - camera.target.x) * t;

    float half = camera.offset.x / camera.zoom;
    if (camera.target.x < half)              camera.target.x = half;
    if (camera.target.x > worldWidth - half) camera.target.x = worldWidth - half;
}


bool sceneChanged(const MatchScreen& match, const MatchScreen& prevMatch){
    return worldOf(match) != worldOf(prevMatch);
}

// void correctCamera(Match& match){
//     switch(match.screen){
//         case KITCHEN:
//         case FRIDGE:
//             match.player.object.pos = match.player.savedPos[WORLD_KITCHEN];
//             setKitchenCamera(match);
//         break;

//         case OVEN:
//             match.player.object.pos = match.player.savedPos[WORLD_OVEN];
//             setOvenCamera(match);
//         break;
//     }
//     // match.prevScreen = match.screen;
// }

void correctCamera(Match& match){
    World from = worldOf(match.prevScreen);
    World to   = worldOf(match.screen);

    //The code has bugs if you can change between OVEN, BOARD and PREPARE without passit throught KITCHEN because of the defaulta case in worldOf
    //So, we need to assert that those changes cannot happen. If they do, there will be problems with the camera corrections and saving the player coordinates
     assert((match.prevScreen == OVEN) == (match.screen == OVEN) ||
           match.prevScreen == KITCHEN || match.prevScreen == FRIDGE ||
           match.screen     == KITCHEN || match.screen     == FRIDGE);

    match.player.savedPos[from] = match.player.object.pos;   // guarda onde saiu
    match.player.object.pos     = match.player.savedPos[to]; // restaura onde entra

    switch(to){
        case WORLD_KITCHEN: setKitchenCamera(match); break;
        case WORLD_OVEN:    setOvenCamera(match);    break;
        default: break;
    }
}


// versão antiga: continua funcionando nas chamadas da cozinha
// void cameraProcess(Camera2D& camera, Player& player, Sprite background) {
//     cameraProcess(camera, player, background.width * GAME_SCALE);
// }

// void cameraProcess(Camera2D& camera, Player& player, Sprite background) {
//     Vector2 targetPos = { player.object.pos.x, player.object.pos.y};

//      float cameraInterpolation = 1.0f - expf(-8.0f * GetFrameTime());

//     camera.target.x += (targetPos.x - camera.target.x) * cameraInterpolation;
//     // camera.target.x += (targetPos.x - camera.target.x) * CAMERA_INTERPOOLATION;

//     if (camera.target.x < camera.offset.x) {
//         camera.target.x = camera.offset.x;
//     }
//     if (camera.target.x > background.width * GAME_SCALE - camera.offset.x) {
//         camera.target.x = background.width * GAME_SCALE - camera.offset.x;
//     }
// }
