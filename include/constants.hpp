#pragma once

#include <iostream>
#include <stdio.h>
#include "raylib.h"
#include "graphic_constants.hpp"

constexpr int FPS = 60;

constexpr Vector2 PLAYER_KITCHEN_POS = {WINDOW_WIDTH/2, WINDOW_HEIGHT*5/7};
constexpr Vector2 PLAYER_OVEN_POS = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
constexpr int PLAYER_HITBOX_RADIUS = 100;
constexpr float PLAYER_SPEED = 10.0f;

constexpr float CAMERA_INTERPOOLATION = 0.2f;

constexpr int COUNTER_SIZE = 3;
constexpr int INVENTORY_SLOTS = 3;

constexpr int MONEY_PER_PERFECT_BURGER = 100;

constexpr int HISTORY_NAME_BUFFER = 50;
constexpr int MIN_ASCII_CODE_SUPPORTED = 32;
constexpr int MAX_ASCII_CODE_SUPPORTED = 126;


//Costumer constants
constexpr float AVERAGE_COSTUMER_PATIENCE = FPS* 60.0f;
constexpr float COSTUMER_PATIENCE_DECAY = 1.0f; // por frame, cliente no balcao cai nisso; na fila cai na metade

constexpr float COSTUMER_TIMER_MAX = FPS * 3.0f;
constexpr float COSTUMER_TIMER_SPEED = 1.0f;

constexpr int MAX_COSTUMER_QUEUE_SIZE = 5;
constexpr int COSTUMERS_PER_MATCH = 10;
constexpr int COSTUMER_LEAVE_TOLERANCE = COSTUMERS_PER_MATCH * 0.7;

constexpr float FIRST_COSTUMER_IN_QUEUE_POS_X = 900.0f;
constexpr float COSTUMER_POS_Y = WINDOW_HEIGHT / 2;
constexpr float COSTUMER_COUNTER_POS_X[COUNTER_SIZE] = {1600, 1400, 1200};

constexpr float COSTUMER_DELTA = 130.0f;
constexpr float COSTUMER_SPEED = 5.0f;


// Decaimento de ingredientes nos heaps (perish_time)
constexpr int INGREDIENT_DECAY_RATE = 1; // por frame
constexpr int COOKABLE_PERISH_TIME = FPS * 90; // 90s guardado no heap antes de estragar

#define PLATE_SIZE 6
#define PAN_NUMBER 3
#define PREPARING_SPACE 3
#define STOARGE_SIZE 8

constexpr float COOK_SPEED = 1.0f;
#define COOK_TIME 2
