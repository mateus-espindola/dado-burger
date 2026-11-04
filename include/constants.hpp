#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>
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
#define BUTTONS_KITCHEN 10
#define BUTTONS_PREPARE 10

#define COOK_SPEED 0.2
#define COOK_TIME 2

#endif
