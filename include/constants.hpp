#pragma once

#include <iostream>
#include <stdio.h>
#include "raylib.h"
#include "graphic_constants.hpp"
#include "gameplay_settings.hpp"

constexpr Vector2 PLAYER_KITCHEN_POS = {WINDOW_WIDTH/2, WINDOW_HEIGHT*5/7};
constexpr Vector2 PLAYER_OVEN_POS = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
constexpr int PLAYER_HITBOX_RADIUS = 100;

constexpr float CAMERA_INTERPOOLATION = 0.2f;

constexpr int COUNTER_SIZE = 3;
constexpr int INVENTORY_SLOTS = 3;

constexpr int HISTORY_NAME_BUFFER = 50;
constexpr int MIN_ASCII_CODE_SUPPORTED = 32;
constexpr int MAX_ASCII_CODE_SUPPORTED = 126;


//Costumer constants
constexpr int MAX_COSTUMER_QUEUE_SIZE = 5;

constexpr float FIRST_COSTUMER_IN_QUEUE_POS_X = 100 * KITCHEN_PNG_SCALE;
constexpr float COSTUMER_POS_Y = WINDOW_HEIGHT / 2 + 30.0f;
constexpr float COSTUMER_COUNTER_POS_X[COUNTER_SIZE] = {215 * KITCHEN_PNG_SCALE, 185 * KITCHEN_PNG_SCALE, 155 * KITCHEN_PNG_SCALE};

constexpr float COSTUMER_DELTA = 130.0f;
constexpr float COSTUMER_SPEED = 5.0f;


#define PLATE_SIZE 6
#define PAN_NUMBER 3
#define PREPARING_SPACE 3
#define STOARGE_SIZE 8

#define COOK_TIME 2
