#pragma once

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

constexpr int HISTORY_NAME_BUFFER = 50;
constexpr int MIN_ASCII_CODE_SUPPORTED = 32;
constexpr int MAX_ASCII_CODE_SUPPORTED = 126;


//Costumer constants
constexpr float AVERAGE_COSTUMER_PATIENCE = 6.0f;

constexpr float COSTUMER_TIMER_MAX = FPS * 6.7f;
constexpr float COSTUMER_TIMER_SPEED = 1.0f;

constexpr int MAX_COSTUMER_QUEUE_SIZE = 10;

constexpr float FIRST_COSTUMER_IN_QUEUE_POS_X = 900.0f;
constexpr float COSTUMER_POS_Y = WINDOW_HEIGHT / 2;
constexpr float COSTUMER_COUNTER_POS_X[COUNTER_SIZE] = {1700, 1600, 1500};

constexpr float COSTUMER_DELTA = 130.0f;
constexpr float COSTUMER_SPEED = 5.0f;


//Inventory draw constants
constexpr float INV_SLOT_SIZE = 90.0f;
constexpr float INV_SLOT_GAP  = 15.0f;
constexpr float INV_X         = 20.0f;   // canto superior esquerdo do inventário
constexpr float INV_Y         = 20.0f;

#define PLATE_SIZE 6
#define PAN_NUMBER 3
#define PREPARING_SPACE 3
#define STOARGE_SIZE 8

constexpr float COOK_SPEED = 1.0f;
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
constexpr int STOVE_WORLD_WIDTH  = WINDOW_WIDTH;   // 2560
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
