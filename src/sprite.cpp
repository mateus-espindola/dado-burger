#include "../include/sprites.hpp"

float spriteDrawnWidth(const Sprite& sprite, float targetHeight) {
    return sprite.width * (targetHeight / (float)sprite.height);
}

void spriteDraw(Sprite& sprite, Vector2 pos, float targetHeight, Color tint) {
    float drawnWidth = spriteDrawnWidth(sprite, targetHeight);

    DrawTexturePro(
        sprite.texture,
        (Rectangle){0, 0, (float)sprite.width, (float)sprite.height},
        (Rectangle){pos.x, pos.y, drawnWidth, targetHeight},
        (Vector2){0, 0},
        0.0f,
        tint
    );
}

void warDetirps(Sprite& sprite, Vector2 pos, float targetHeight, Color tint) {
    float drawnWidth = spriteDrawnWidth(sprite, targetHeight);

    DrawTexturePro(
        sprite.texture,
        (Rectangle){(float)sprite.width, 0, (float)sprite.width * -1, (float)sprite.height},
        (Rectangle){pos.x, pos.y, drawnWidth, targetHeight},
        (Vector2){0, 0},
        0.0f,
        tint
    );
}

void loadSpritesheet(Sprite sprites[]) {
    // Array apenas com os caminhos, na mesma ordem dos enums (0, 1, ...)
    const char *paths[QUANTITY_OF_SPRITES] = {
        [SPR_KITCHEN] = "assets/sprites/kitchen.png",
        [SPR_PLAYER]     = "assets/sprites/player.png",
        [SPR_INGREDIENTS] = "assets/sprites/ingredients.png",
        [SPR_COSTUMERS] = "assets/sprites/costumers.png",
        [SPR_KITCHEN_BACKGROUND] = "assets/sprites/kitchen_background.png",
        [SPR_MENU_BACKGROUND] = "assets/sprites/menu_background.png",
        [SPR_HOW_TO_PLAY] = "assets/sprites/how_to_play.png"
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
