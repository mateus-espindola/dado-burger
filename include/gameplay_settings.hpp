#pragma once

constexpr int FPS = 60;


// Player
constexpr float PLAYER_SPEED = 10.0f;

constexpr int MONEY_PER_PERFECT_BURGER = 100;


// Costumers
constexpr float AVERAGE_COSTUMER_PATIENCE = FPS* 180.0f;
constexpr float COSTUMER_PATIENCE_DECAY = 1.0f; // por frame

constexpr float COSTUMER_TIMER_MAX = FPS * 90.0f; // Tempo até o proximo cliente aparecer
constexpr float COSTUMER_TIMER_SPEED = 1.0f;

constexpr int COSTUMERS_PER_MATCH = 10;
constexpr int COSTUMER_LEAVE_TOLERANCE = COSTUMERS_PER_MATCH * 0.7; // Porcentagem de costumers que devem ser atendidos obrigatoriamente


// Ingredientes
constexpr int INGREDIENT_DECAY_RATE = 1; // por frame
constexpr int COOKABLE_PERISH_TIME = FPS * 90; // Tempo guardado no heap antes de estragar

constexpr float COOK_SPEED = 1.0f;
constexpr float MEAT_EXTRA_COOK_SPEED = 0.75f;
