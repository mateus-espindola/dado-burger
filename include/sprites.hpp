#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "raylib.h"

/* ============================ */
/*            SPRITES           */
/* ============================ */

enum SpriteType {
    SPR_BACKGROUND,
    SPR_PLAYER,
    QUANTITY_OF_SPRITES
};

struct Sprite {
    Texture2D texture;
    int width, height;
};


void spriteDraw(Sprite& sprite, Vector2 pos, float scale, Color tint);

void warDetirps(Sprite& sprite, Vector2 pos, float scale, Color tint);

void loadSpritesheet(Sprite sprites[]);

void unloadSpritesheet(Sprite sprites[]);

#endif