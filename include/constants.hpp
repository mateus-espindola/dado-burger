#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>
#include <stdio.h>
#include "raylib.h"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr int FPS = 60;
constexpr float GAME_SCALE = ((float) WINDOW_HEIGHT) / 96.0f;

constexpr Vector2 PLAYER_KITCHEN_POS = {/*WINDOW_WIDTH/2*/ 4200, WINDOW_HEIGHT*2/3};
constexpr Vector2 PLAYER_OVEN_POS = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
constexpr int PLAYER_HITBOX_RADIUS = 100;
constexpr float PLAYER_SPEED = 10.0f;

constexpr float CAMERA_INTERPOOLATION = 0.2f;

constexpr int COUNTER_SIZE = 3;

constexpr int INVENTORY_SLOTS = 3;


//Inventory draw constants
constexpr float INV_SLOT_SIZE = 90.0f;
constexpr float INV_SLOT_GAP  = 15.0f;
constexpr float INV_X         = 20.0f;   // canto superior esquerdo do inventário
constexpr float INV_Y         = 20.0f;

//CONSTANTES ADICIONADAS:
#define PLATE_SIZE 6
#define PAN_NUMBER 3
#define PREPARING_SPACE 3
#define STOARGE_SIZE 8

#define COOK_SPEED 0.2
#define COOK_TIME 2


#define DRAW_HITBOX 0




#define BOARD_W 400
#define BOARD_H 220
#define BOARD_X ((WINDOW_WIDTH - BOARD_W) / 2)
#define BOARD_Y ((WINDOW_HEIGHT - BOARD_H) / 2)

// Stacks
#define STACK_W      90
#define STACK_H      90
#define STACK_GAP    30   // espaço vertical entre stacks
#define STACK_MARGIN 40   // espaço horizontal entre stack e tábua
#define STACKS_LEFT  3
#define STACKS_RIGHT 2




// Mundo do fogão: duas vezes a largura da tela
constexpr int STOVE_WORLD_WIDTH  = WINDOW_WIDTH * 2;   // 2560
constexpr int STOVE_WORLD_HEIGHT = WINDOW_HEIGHT;

constexpr float STOVE_MARGIN = 60.0f;
constexpr float PANEL_Y      = STOVE_MARGIN;
constexpr float PANEL_H      = STOVE_WORLD_HEIGHT - 2 * STOVE_MARGIN;
constexpr float PANEL_GAP    = 60.0f;

// Larguras das três seções (somam o que cabe entre as margens)
constexpr float PLATE_W   = 1000.0f;   // chapa (esquerda)
constexpr float SQUARES_W = 800.0f;    // 2 colunas de quadrados (meio)
constexpr float CIRCLES_W = STOVE_WORLD_WIDTH - 2 * STOVE_MARGIN
                            - PLATE_W - SQUARES_W - 2 * PANEL_GAP;   // coluna de círculos (direita)

constexpr float PLATE_X   = STOVE_MARGIN;
constexpr float SQUARES_X = PLATE_X + PLATE_W + PANEL_GAP;
constexpr float CIRCLES_X = SQUARES_X + SQUARES_W + PANEL_GAP;

#endif
