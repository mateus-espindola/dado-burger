#include "world.hpp"
#include "match.hpp"

//Returns the width of the scene. It is used to call the camera function with the proper scene size to find target and things like that
float worldWidthOf(const Match &match) {
    switch (match.screen) {
        case KITCHEN:
        case FRIDGE:
            return match.spriteMatch[SPR_BACKGROUND].width * GAME_SCALE;
        case OVEN:
            return STOVE_WORLD_WIDTH;
        default:
            return WINDOW_WIDTH;
    }
}

World worldOf(MatchScreen s) {
    switch (s) {
        case OVEN: return WORLD_OVEN;
        default:   return WORLD_KITCHEN;   // KITCHEN e FRIDGE são o mesmo mundo
    }
}

//Returns the limit of the scene. It is used to call the camera function with the proper scene size to find target and things like that
Limits playerLimitsOf(const Match &match) {
    float halfW = (match.player.object.sprite.width * GAME_SCALE) / 2;

    switch (match.screen) {
        case OVEN: { //Those are necessary because the compiler has troubles with the variables initialized in the case
            float halfScreen = match.camera.offset.x / match.camera.zoom;
            float world      = worldWidthOf(match);
            return { halfScreen, world - halfScreen };
        }
        default:
            return { halfW, worldWidthOf(match) - halfW };
    }
}