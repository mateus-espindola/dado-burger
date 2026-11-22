#include "../include/match.hpp"
#include "../include/camera.hpp"

void matchStart(Match& match) {
    initializeQueue(match.costumer_line);
    for (int i = 0; i < COUNTER_SIZE; i++) {
        match.costumer_counter[i].type = EMPTY;
    }

    match.screen = KITCHEN;

    setIngredients(match.buttonsVec, STATE_QUANTITY);

    setPlayer(match.player);

    setKitchenCamera(match);
}

void matchEnd(Match& match) {
    exterminateQueue(match.costumer_line);
    for (int i=0; i<COUNTER_SIZE; i++) {
        match.costumer_counter[i].type = EMPTY;
    }

    for (int s = 0; s < STATE_QUANTITY; s++) {
        ButtonVec& screen = match.buttonsVec[s];
        if (screen.buttons == nullptr) continue;

        for (int i = 0; i < screen.size; i++) {
            Button& b = screen.buttons[i];

            stack_destroy(b.target); // esvazia os nodes e zera type/size, sem tocar na capacidade

            // Nao usa exterminateHeap: ela libera o array e zera capacity, o que inviabilizaria
            // o proximo insertHeap depois de um matchStart (size==capacity==0 rejeitaria tudo).
            // So precisa esvaziar o que importa pro reuso.
            b.heap.size = 0;
            b.heap.type = NONE;
        }
    }
}

void winMatch(Match &match) {
    match.screen = VICTORY;
    match.nameInput[0] = '\0';
    match.nameInputLen = 0;
}

void loseMatch(Match &match) {
    match.screen = DEFEAT;
}

void playerProcess(Player& player) {
    if (IsKeyDown(KEY_RIGHT)) player.object.pos.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.object.pos.x -= 4;
}

// Empilha "count" ingredientes "c" na pilha, no ponto de preparo ja definido por initIngredient
static void fillStack(Stack& s, char c, int count) {
    for (int i = 0; i < count; i++) {
        Ingredient ing;
        initIngredient(ing, c);
        stack_push(s, ing);
    }
}

// Igual, mas forca o ponto de preparo pra READY (cutIngredient so marca READY, sem alterar o tipo)
static void fillStackReady(Stack& s, char c, int count) {
    for (int i = 0; i < count; i++) {
        Ingredient ing;
        initIngredient(ing, c);
        cutIngredient(ing);
        stack_push(s, ing);
    }
}

// Preenche as pilhas/heaps de todas as telas antes da partida comecar.
void setIngredients(ButtonVec screens[], int screenCount) {
    (void)screenCount;

    Button* prepareBut = screens[PREPARE].buttons;
    fillStackReady(prepareBut[0].target, 'S', 3); // SWISS_CHEESE
    fillStackReady(prepareBut[1].target, 'C', 3); // CHEDDAR
    fillStackReady(prepareBut[2].target, 'L', 3); // LETTUCE
    fillStackReady(prepareBut[3].target, 'T', 3); // TOMATO
    fillStackReady(prepareBut[4].target, 'O', 3); // ONION

    Button* ovenBut = screens[OVEN].buttons;
    fillStack(ovenBut[0].target, 'M', 5); // MEAT, RAW
    fillStack(ovenBut[1].target, 'E', 3); // EGG, RAW
    fillStack(ovenBut[2].target, 'B', 3); // BACON, RAW

    Button* boardBut = screens[BOARD].buttons;
    fillStack(boardBut[0].target, 'L', 3); // LETTUCE, NEEDS_TO_CUT
    fillStack(boardBut[1].target, 'T', 3); // TOMATO, NEEDS_TO_CUT
    fillStack(boardBut[2].target, 'O', 3); // ONION, NEEDS_TO_CUT
    fillStack(boardBut[3].target, 'S', 3); // SWISS_CHEESE, NEEDS_TO_CUT
    fillStack(boardBut[4].target, 'C', 3); // CHEDDAR, NEEDS_TO_CUT
}
