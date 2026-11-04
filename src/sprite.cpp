#include "sprites.hpp"

void spriteDraw(Sprite& sprite, Vector2 pos, float scale, Color tint) {
    DrawTexturePro(
        sprite.texture,
        (Rectangle){0, 0, (float)sprite.width, (float)sprite.height},
        (Rectangle){pos.x, pos.y, (float)sprite.width * scale, (float)sprite.height * scale},
        (Vector2){0, 0},
        0.0f,
        tint
    );
}

void warDetirps(Sprite& sprite, Vector2 pos, float scale, Color tint) {
    DrawTexturePro(
        sprite.texture,
        (Rectangle){(float)sprite.width, 0, (float)sprite.width * -1, (float)sprite.height},
        (Rectangle){pos.x, pos.y, (float)sprite.width * scale, (float)sprite.height * scale},
        (Vector2){0, 0},
        0.0f,
        tint
    );
}