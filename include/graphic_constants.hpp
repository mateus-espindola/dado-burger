#pragma once

// Constantes puramente graficas (janela, escala, tamanhos e posicoes de desenho).
// Constantes de gameplay/simulacao continuam em constants.hpp.

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr float GAME_SCALE = ((float) WINDOW_HEIGHT) / 96.0f;

// Altura nativa (em pixels) do canvas do kitchen.png no Aseprite. O fundo e desenhado
// com altura travada em WINDOW_HEIGHT preservando a proporcao (spriteDrawnWidth), entao
// qualquer posicao/tamanho medido direto no Aseprite (em pixels do canvas) corresponde
// a essa mesma fracao da tela: so multiplicar por KITCHEN_PNG_SCALE.
// Ex.: sino em (237, 74), 11x7 no Aseprite -> na tela fica em
// (237*KITCHEN_PNG_SCALE, 74*KITCHEN_PNG_SCALE), tamanho (11*KITCHEN_PNG_SCALE, 7*KITCHEN_PNG_SCALE).
// Atualiza KITCHEN_PNG_HEIGHT se o canvas for redimensionado de novo no Aseprite.
constexpr float KITCHEN_PNG_HEIGHT = 120.0f;
constexpr float KITCHEN_PNG_SCALE  = WINDOW_HEIGHT / KITCHEN_PNG_HEIGHT;

constexpr int INGREDIENT_RADIUS = 3*16.0f;

// Atlas de ingredientes: grid 24x24, linha = ingrediente, coluna = CookPoint
// (NEEDS_TO_CUT, READY, RAW, RARE, MEDIUM_RARE, WELL_DONE, OVER_COOKED, nessa ordem).
constexpr int INGREDIENT_ATLAS_CELL = 24;
constexpr int INGREDIENT_ATLAS_COLS = 7;

constexpr float PLAYER_HEIGHT = 0.45 * WINDOW_HEIGHT;

constexpr float BUTTON_OPACITY = 0.1f;

// Barra de decaimento desenhada do lado do heap quando o mouse esta por cima
constexpr float ROT_BAR_W   = 10.0f;
constexpr float ROT_BAR_GAP = 10.0f;

//Inventory draw constants
constexpr float INV_SLOT_SIZE = 90.0f;
constexpr float INV_SLOT_GAP  = 15.0f;
constexpr float INV_X         = 20.0f;   // canto superior esquerdo do inventário
constexpr float INV_Y         = 20.0f;

#define DRAW_HITBOX 0

#define BOARD_W 400
#define BOARD_H 220
#define BOARD_X ((WINDOW_WIDTH - BOARD_W) / 2)
#define BOARD_Y ((WINDOW_HEIGHT - BOARD_H) / 2)

// Stacks (colunas decorativas desenhadas do lado da tabua)
#define STACK_W      90
#define STACK_H      90
#define STACK_GAP    30   // espaço vertical entre stacks
#define STACK_MARGIN 40   // espaço horizontal entre stack e tábua
#define STACKS_LEFT  3
#define STACKS_RIGHT 2

constexpr int STOVE_WORLD_WIDTH  = WINDOW_WIDTH;
constexpr int STOVE_WORLD_HEIGHT = WINDOW_HEIGHT;

constexpr float STOVE_MARGIN = 30;
constexpr float PANEL_Y      = STOVE_MARGIN;
constexpr float PANEL_H      = STOVE_WORLD_HEIGHT - 2 * STOVE_MARGIN;

// Larguras das três seções (somam o que cabe entre as margens)
constexpr float SQUARES_W = WINDOW_WIDTH / 4 - 2*STOVE_MARGIN;   // Stacks a serem grilladas
constexpr float PLATE_W   = WINDOW_WIDTH / 2 - 2*STOVE_MARGIN;   // chapa
constexpr float READIES_W = SQUARES_W;

constexpr float SQUARES_X = STOVE_MARGIN;
constexpr float PLATE_X   = SQUARES_X + SQUARES_W + 2*STOVE_MARGIN;
constexpr float READIES_X = PLATE_X + PLATE_W + 2*STOVE_MARGIN;

constexpr float READIES_Y = PANEL_Y + PANEL_H / 3;
constexpr float READIES_H = PANEL_H * 2/3;
