#include <math.h>

#include "../include/camera.hpp"

void setCamera(Match& match){
    
    match.camera = { 0 };

    match.camera.target = match.player.pos;
    match.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    match.camera.zoom   = 1.0f;

}

void cameraUpdate(Match& match){
    float t = 1.0f - expf(-8.0f * GetFrameTime());
    match.camera.target.x += (match.player.pos.x - match.camera.target.x) * t;
    match.camera.target.y += (match.player.pos.y - match.camera.target.y) * t;
}