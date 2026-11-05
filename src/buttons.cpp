#include <cstdio>
#include <cmath>

#include "../include/buttons.hpp"
#include "../include/match.hpp"    // para STATE_QUANTITY, PREPARE, BOARD, OVEN

static void setButton(Button &b, float x, float y, float w, float h, const char *text) {
    b.shape = { x, y, w, h };
    b.pos   = { x, y };
    b.size  = { w, h };
    snprintf(b.text, sizeof(b.text), "%s", text);
}

void declareButtons(Button **buttons, int size) {
    // static: os arrays vivem até o fim do programa
    static Button prepareBut[BUTTONS_PREPARE];
    static Button boardBut[BUTTONS_BOARD];
    static Button ovenBut[BUTTONS_OVEN];

    buttons[PREPARE] = prepareBut;
    buttons[BOARD]   = boardBut;
    buttons[OVEN]    = ovenBut;

    // Índice 0 = botão da tela principal de cada estado
    setButton(prepareBut[0], PREPARE_LEFT_X, PREPARE_LEFT_Y, PREPARE_LEFT_W, PREPARE_LEFT_H, "PREPARE");
    setButton(boardBut[0],   BOARD_LEFT_X,   BOARD_LEFT_Y,   BOARD_LEFT_W,   BOARD_LEFT_H,   "BOARD");
    setButton(ovenBut[0],    OVEN_LEFT_X,    OVEN_LEFT_Y,    OVEN_LEFT_W,    OVEN_LEFT_H,    "OVEN");
}

int nearestButtonIndex(float playerX, Button **buttons) {
    int nearest = -1;
    float bestDist = INFINITY;

    for (int i = 0; i < STATE_QUANTITY; i++) {
        if (buttons[i] == nullptr) continue;

        const Button &b = buttons[i][0];

        // pos é o canto superior esquerdo, então usamos o centro do botão
        float centerX = b.pos.x + b.size.x / 2.0f;

        // Em um jogo lateral, só a distância horizontal costuma importar
        float dist = fabsf(playerX - centerX);

        if (dist < bestDist && dist <= MAX_ACESS_DIST) {
            bestDist = dist;
            nearest = i;
        }
    }

    return nearest;
}