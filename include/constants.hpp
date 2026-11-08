#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// #include <iostream>
#include "raylib.h"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr int FPS = 60;
constexpr float GAME_SCALE = ((float) WINDOW_HEIGHT) / 96.0f;

constexpr Vector2 PLAYER_START_POS = {WINDOW_WIDTH/2, WINDOW_HEIGHT*2/3};
constexpr int PLAYER_HITBOX_RADIUS = 100;
constexpr float PLAYER_SPEED = 10.0f;

constexpr float CAMERA_INTERPOOLATION = 0.2f;

constexpr int COUNTER_SIZE = 3;

//CONSTANTES ADICIONADAS:
#define PLATE_SIZE 6
#define PAN_NUMBER 3
#define PREPARING_SPACE 3
#define STOARGE_SIZE 8

#define BUTTONS_COUNTER 10
#define BUTTONS_KITCHEN 3
#define BUTTONS_FRIDGE 10
#define BUTTONS_PREPARE 10
#define BUTTONS_BOARD 10
#define BUTTONS_OVEN 10

#define COOK_SPEED 0.2
#define COOK_TIME 2


#define DRAW_HITBOX 1




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

#endif
