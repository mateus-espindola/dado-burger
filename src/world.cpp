#include "../include/world.hpp"
#include "../include/match.hpp"
#include "../include/graphic_constants.hpp"

//Returns the width of the scene. It is used to call the camera function with the proper scene size to find target and things like that
float worldWidthOf(const Match &match) {
    switch (match.screen) {
        case KITCHEN:
        case FRIDGE:
            return spriteDrawnWidth(match.spriteMatch[SPR_BACKGROUND], WINDOW_HEIGHT);
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
    float halfW = spriteDrawnWidth(match.player.object.sprite, PLAYER_HEIGHT) / 2;

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
