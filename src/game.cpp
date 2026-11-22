#include <cstdio>
#include <cstring>
#include <string>

#include "../include/game.hpp"
#include "../include/graphics.hpp"
#include "../include/inputs.hpp"
#include "../include/camera.hpp"
#include "../include/world.hpp"

#include "raylib.h"

bool readFiles(Game& game, FILE* fp, FILE* fh) {
    if (fp == nullptr) {
        std::cout << "There was an error while trying to read the orders archive." << std::endl;
        return false;
    }
    if (fh == nullptr) {
        std::cout << "There was an error while trying to read the history archive." << std::endl;
        return false;
    }

    initializeHashTable(game.hashtable_orders); // capacity=0 sem isso: update_load_factor faria size/0

    // Loads fp
    int cod;
    while (fscanf(fp, "%d\n", &cod) == 1) {
        std::string ingredients;

        char buffer[16];
        if (fgets(buffer, sizeof(buffer), fp)) {
            // Fazer essa maracutaia pra remover o \n do final da string
            std::string strIngredient(buffer);
            if (!strIngredient.empty() && strIngredient.back() == '\n') {
                strIngredient.pop_back();
            }

            Order newOrder = {cod, strIngredient};

            game.avl_orders.root = insertAVL(game.avl_orders.root, newOrder);
        }
    }
    game.avl_orders.last_cod = cod;

    // Loads fh
    int historyLines = 0;
    char countBuffer[HISTORY_NAME_BUFFER];
    while (fgets(countBuffer, sizeof(countBuffer), fh)) historyLines++;
    rewind(fh);
    initializeContiguousList(game.historico, historyLines / 2 + 1);

    char buffer[HISTORY_NAME_BUFFER];
    int pos = 0;
    while (fgets(buffer, sizeof(buffer), fh)) {
        std::string strName(buffer);
        if (!strName.empty() && strName.back() == '\n') {
            strName.pop_back();
        }

        int score;
        if (fscanf(fh, "%d\n", &score)) {
            PlayerInfo newInfo = {strName, score};

            insertContiguousList(game.historico, newInfo, pos);
            pos++;
        }
    }

    return true;
}

void gameStart(Game& game){
    Match &match = game.current_match;
    // loadSpritesheet(game.spritesMenu);
    loadSpritesheet(match.spriteMatch);

    match.player.object.sprite = match.spriteMatch[SPR_PLAYER];
    match.player.object.radius = PLAYER_HITBOX_RADIUS;

    declareMenuButtons(game.menuButtons);
    declareHistoryButtons(game.historyButtons);
    game.historyPage = 0;
    game.historySortByName = false;

    game.state = MENU;
    game.quit = false;
}

void processMenuButClick(Game& game, Button& button){
    if      (strcmp(button.text, "PLAY") == 0)        {game.state = PLAYING; matchStart(game.current_match); }
    else if (strcmp(button.text, "HOW TO PLAY") == 0) game.state = HOW_TO_PLAY;
    else if (strcmp(button.text, "HISTORY") == 0)     { game.state = HISTORY; game.historyPage = 0; }
    else if (strcmp(button.text, "QUIT") == 0)        game.quit = true;
}

void menuProcess(Game& game, Vector2 mouse){
    int butUnderMouseInd = findUIButtonUnderMouse(mouse, game.menuButtons);

    drawMenu(game.menuButtons, butUnderMouseInd);

    if (butUnderMouseInd != -1 && mouseKeyLeftClicked())
        processMenuButClick(game, game.menuButtons.buttons[butUnderMouseInd]);
}

int historyTotalPages(const Game& game){
    int totalPages = (game.historico.size + HISTORY_ENTRIES_PER_PAGE - 1) / HISTORY_ENTRIES_PER_PAGE;
    return (totalPages < 1) ? 1 : totalPages;
}

void sortHistory(Game& game){
    if (game.historySortByName) stringRadixSort(game.historico);
    else                         partitionSort(game.historico);
}

void processHistoryButClick(Game& game, Button& button){
    int totalPages = historyTotalPages(game);

    if      (strcmp(button.text, "BACK") == 0) game.state = MENU;
    else if (strcmp(button.text, "<<")   == 0) game.historyPage = 0;
    else if (strcmp(button.text, "PREV") == 0) { if (game.historyPage > 0) game.historyPage--; }
    else if (strcmp(button.text, "NEXT") == 0) { if (game.historyPage < totalPages - 1) game.historyPage++; }
    else if (strcmp(button.text, ">>")   == 0) game.historyPage = totalPages - 1;
    else if (strncmp(button.text, "SORT:", 5) == 0) {
        game.historySortByName = !game.historySortByName;
        snprintf(button.text, sizeof(button.text), "%s", game.historySortByName ? "SORT: NAME" : "SORT: SCORE");
        sortHistory(game);
        game.historyPage = 0;
    }
}

void historyProcess(Game& game, Vector2 mouse){
    int butUnderMouseInd = findUIButtonUnderMouse(mouse, game.historyButtons);

    drawHistory(game.historico, game.historyPage, game.historyButtons, butUnderMouseInd);

    if (butUnderMouseInd != -1 && mouseKeyLeftClicked())
        processHistoryButClick(game, game.historyButtons.buttons[butUnderMouseInd]);
}

void gameProcess(Game& game){
    if (IsKeyPressed(KEY_ESCAPE)) game.quit = true;

    Vector2 mouse = findMousePos();

    switch(game.state) {

        case MENU:
            menuProcess(game, mouse);
        break;

        case HOW_TO_PLAY:
            // tutorialProcess();
            // drawHowToPlay();
        break;

        case HISTORY:
            historyProcess(game, mouse);
        break;

        case PLAYING:
            ambientProcess(game, mouse); //Mostra os botoes e desenha o fundo de acordo com o ambiente
        break;

    }
}

void sortReadyIngredients(Match& match, MatchScreen screen) {
    Button* prepareBut = match.buttonsVec[PREPARE].buttons;

    if (screen == BOARD) {
        Stack& readyStack = match.buttonsVec[BOARD].buttons[5].target;

        int count = readyStack.size; // cachear: stack_pop muda o size a cada volta
        for (int i = 0; i < count; i++) {
            Ingredient aux;
            stack_pop(readyStack, aux);

            switch (aux.type) {
                case SWISS_CHEESE: stack_push(prepareBut[0].target, aux); break;
                case CHEDDAR:      stack_push(prepareBut[1].target, aux); break;
                case LETTUCE:      stack_push(prepareBut[2].target, aux); break;
                case TOMATO:       stack_push(prepareBut[3].target, aux); break;
                case ONION:        stack_push(prepareBut[4].target, aux); break;
                default: break;
            }
        }
    }

    if (screen == OVEN) {
        Heap<Ingredient>& readyHeap = match.buttonsVec[OVEN].buttons[9].heap;

        int count = readyHeap.size; // mesmo motivo acima
        for (int i = 0; i < count; i++) {
            Ingredient aux = getMinValueHeap(readyHeap);

            switch (aux.type) {
                case MEAT:
                    if (practicalCookingStateOf(aux) == RARE) {
                        insertHeap(prepareBut[8].heap, aux);
                        break;
                    }
                    if (practicalCookingStateOf(aux) == MEDIUM_RARE) {
                        insertHeap(prepareBut[9].heap, aux);
                        break;
                    }
                    insertHeap(prepareBut[10].heap, aux); // WELL_DONE, OVER_COOKED ou qualquer outro caso
                break;

                case EGG:
                    insertHeap(prepareBut[11].heap, aux);
                break;

                case BACON:
                    insertHeap(prepareBut[12].heap, aux);
                break;

                default: break;
            }
        }
    }
}

void leaveScreen(Match& match) {
    MatchScreen curentScreen = match.screen;
    if (curentScreen == OVEN || curentScreen == BOARD) {
        sortReadyIngredients(match, curentScreen);
    }
    match.screen = KITCHEN;
}


void processPauseButClick(Game& game, Button& button){
    Match& match = game.current_match;

    if (strcmp(button.text, "RESUME MATCH") == 0) {
        match.screen = match.screenBeforePause;
    }
    else if (strcmp(button.text, "RESTART MATCH") == 0) {
        matchEnd(match);
        matchStart(match); // reseta player, camera, costumers e reenche os ingredientes
    }
    else if (strcmp(button.text, "QUIT MATCH") == 0) {
        finishCurrentMatch(game);
    }
}

static void appendToHistoryFile(const char* path, const char* name, int score);

void ambientProcess(Game& game, Vector2 mouse){

    Match &match = game.current_match;

    // PAUSED/VICTORY/DEFEAT nao tem mundo/camera propria e podem ser alcancados direto
    // do OVEN (unico MatchScreen com WORLD_OVEN) via TAB ou finishCurrentMatch. Pular a
    // correcao nesses casos evita acionar o assert de correctCamera (que so aceita
    // transicoes de/pra OVEN passando por KITCHEN/FRIDGE).
    bool noWorldScreen        = match.screen     == PAUSED || match.screen     == VICTORY || match.screen     == DEFEAT;
    bool noWorldPrevScreen    = match.prevScreen == PAUSED || match.prevScreen == VICTORY || match.prevScreen == DEFEAT;

    if (!noWorldScreen && !noWorldPrevScreen && sceneChanged(match.screen, match.prevScreen))
        correctCamera(match);
    match.prevScreen = match.screen;
    // printf("%d\n", match.player.selectedSlot);

    if (match.screen == KITCHEN || match.screen == FRIDGE)
        match.screen = (match.player.object.pos.x > KITCHEN_FRIDGE_BOUNDARY_X) ? FRIDGE : KITCHEN;

    int selectedInvSlot = changeInvSlot();
    if(selectedInvSlot != -1 && selectedInvSlot < INVENTORY_SLOTS)
        match.player.selectedSlot = selectedInvSlot;
    printf("%d ", match.player.selectedSlot + 1);
    printf("%d ", match.player.inventory[match.player.selectedSlot].size);
    printf("%d ", match.player.inventory[match.player.selectedSlot].capacity);
    printf("%d\n", match.player.inventory[match.player.selectedSlot].type);


    // 1. update
    if (match.screen != PAUSED && match.screen != VICTORY && match.screen != DEFEAT) {
        cookAll(match.buttonsVec);
        processRottingIngredients(match.buttonsVec);
        processCostumers(match.costumer_line, match.costumer_counter, game.avl_orders, game.hashtable_orders);

        if (IsKeyPressed(KEY_TAB)) {
            match.screenBeforePause = match.screen;
            match.screen = PAUSED;
        }

        if (match.costumer_line.costumers_generated >= COSTUMERS_PER_MATCH) {
            if (IsKeyPressed(KEY_F)) {
                finishCurrentMatch(game);
            }
        }

        if (IsKeyDown(KEY_M)) match.player.money += 5;

        if (match.costumer_line.costumers_that_left > COSTUMERS_PER_MATCH - COSTUMER_LEAVE_TOLERANCE) {
            loseMatch(match);
            matchEnd(match); // mesma limpeza que finishCurrentMatch faz no caminho de vitoria
        }
    }

    // Player/camera so existem nas telas com mundo/camera propria (ver usesCamera()).
    // PREPARE e BOARD sao desenhados em espaco de tela (sem BeginMode2D) e compartilham
    // WORLD_KITCHEN em worldOf, entao sceneChanged nunca dispara correctCamera ao voltar
    // pra KITCHEN - se playerProcess/cameraProcess rodassem aqui usando os limites default
    // (WINDOW_WIDTH, de playerLimitsOf/worldWidthOf), eles empurrariam player.object.pos e
    // match.camera.target pra fora do mundo real da KITCHEN, e isso nunca seria corrigido.
    switch(match.screen){
        case KITCHEN:
        case FRIDGE:
        case OVEN:
            playerProcess(match.player, playerLimitsOf(match).min , playerLimitsOf(match).max);
            cameraProcess(match.camera, match.player, worldWidthOf(match));
        break;
        default: break;
    }

    // o índice é calculado depois do update, com a câmera já atualizada
    int butUnderMouseInd = findButtonUnderMouse(mouse, match.buttonsVec[match.screen], match.camera, match.screen);

    // 2. draw
    switch(match.screen){
        case KITCHEN:
        case FRIDGE: drawKitchen(match, butUnderMouseInd);  break;
        case OVEN:   drawStove(match, butUnderMouseInd);    break;
        case BOARD:  drawBoard(match, butUnderMouseInd);    break;
        case PREPARE: drawPrepare(match, butUnderMouseInd); break;
        case PAUSED: drawPause(match, butUnderMouseInd);    break;
        case VICTORY: drawVictory(match, butUnderMouseInd); break;
        case DEFEAT: drawDefeat(match, butUnderMouseInd);   break;
        default: break;
    }

    // 3. click
    switch(match.screen){
        case KITCHEN: { //The brackets garantee that the variable nearest only exists in the brackets and can't be used elsewhere in the switch so that we don't have de problem of an unnitialized veriable being used
            int nearest = nearestButtonIndex(match.player.object.pos.x, match.buttonsVec[match.screen]);
            if (keyUpClicked() && nearest != -1)
                processButClick(match, match.buttonsVec[match.screen].buttons[nearest]);

            if (mouseKeyLeftClicked()) {
                Vector2 mouseWorld = GetScreenToWorld2D(mouse, match.camera);
                giveBurgerToCostumer(match.costumer_counter, match.player, mouseWorld);
            }

            if (IsKeyPressed(KEY_P)) {
                Vector2 mouseWorld = GetScreenToWorld2D(mouse, match.camera);
                cheatGivePerfectBurger(match.costumer_counter, match.player, mouseWorld);
            }
        } break;
        case PREPARE:
        case OVEN:
        case BOARD:
            if(keyDownClicked()) leaveScreen(match);
        case FRIDGE:
            if(butUnderMouseInd != -1){
                Button& but = match.buttonsVec[match.screen].buttons[butUnderMouseInd];
                if (mouseKeyLeftClicked())
                    processButClick(match, but);
            }
        break;

        case PAUSED:
            if (butUnderMouseInd != -1 && mouseKeyLeftClicked())
                processPauseButClick(game, match.buttonsVec[PAUSED].buttons[butUnderMouseInd]);
        break;

        case VICTORY: {
            // digita o nome (igual ao TrabalhoFinalAlgProg: GetCharPressed + filtro ASCII imprimivel)
            if (match.nameInputLen < HISTORY_NAME_BUFFER - 1) {
                int c = GetCharPressed();
                if (c >= MIN_ASCII_CODE_SUPPORTED && c <= MAX_ASCII_CODE_SUPPORTED) {
                    match.nameInput[match.nameInputLen] = (char)c;
                    match.nameInputLen++;
                    match.nameInput[match.nameInputLen] = '\0';
                }
            }
            if (match.nameInputLen > 0 && IsKeyPressed(KEY_BACKSPACE)) {
                match.nameInputLen--;
                match.nameInput[match.nameInputLen] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && match.nameInputLen > 0) {
                appendToHistoryFile(game.historicoPath, match.nameInput, match.player.money);

                PlayerInfo info = { std::string(match.nameInput), match.player.money };
                insertContiguousList(game.historico, info, game.historico.size);

                game.state = MENU;
            }
        } break;

        case DEFEAT:
            if (IsKeyPressed(KEY_ENTER)) game.state = MENU;
        break;

        default: break;
    }
}

void finishCurrentMatch(Game& game) {
    Match& match  = game.current_match;

    winMatch(match);

    matchEnd(match);

    // game.state fica em PLAYING: a tela de VICTORY/DEFEAT (match.screen) ainda precisa
    // ser mostrada e, no caso de vitoria, o nome precisa ser digitado antes de voltar ao menu
}

// Salva nome+pontuacao no fim do arquivo de historico (mesmo formato que readFiles le: nome\npontos\n)
static void appendToHistoryFile(const char* path, const char* name, int score) {
    FILE* f = fopen(path, "a");
    if (f == nullptr) return;

    fprintf(f, "%s\n%d\n", name, score);
    fclose(f);
}

void gameOver(Game& game){
    // unloadSpritesheet(game.spritesMenu);
    unloadSpritesheet(game.current_match.spriteMatch);
}
