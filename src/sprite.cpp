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

void loadSpritesheet(Sprite sprites[]) {
    // Array apenas com os caminhos, na mesma ordem dos enums (0, 1, ...)
    const char *paths[QUANTITY_OF_SPRITES] = {
        [SPR_BACKGROUND] = "assets/sprites/background.png",
        [SPR_PLAYER]     = "assets/sprites/player.png"
    };

    for (int i = 0; i < QUANTITY_OF_SPRITES; i++) {
        sprites[i].texture = LoadTexture(paths[i]);
        sprites[i].width   = sprites[i].texture.width;
        sprites[i].height  = sprites[i].texture.height;
    }
}

void unloadSpritesheet(Sprite sprites[]) {
    for (int i = 0; i < QUANTITY_OF_SPRITES; i++) {
        UnloadTexture(sprites[i].texture);
    }
}