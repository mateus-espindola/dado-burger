#pragma once

#include "raylib.h"

/* ============================ */
/*            SPRITES           */
/* ============================ */

enum SpriteType {
    SPR_KITCHEN,
    SPR_PLAYER,
    QUANTITY_OF_SPRITES
};

struct Sprite {
    Texture2D texture;
    int width, height;
};


// Largura na tela quando o sprite e desenhado com essa altura, preservando a proporcao
// original da textura. Assim o tamanho final nao depende da resolucao do PNG carregado.
float spriteDrawnWidth(const Sprite& sprite, float targetHeight);

void spriteDraw(Sprite& sprite, Vector2 pos, float targetHeight, Color tint);

void warDetirps(Sprite& sprite, Vector2 pos, float targetHeight, Color tint);

void loadSpritesheet(Sprite sprites[]);

void unloadSpritesheet(Sprite sprites[]);