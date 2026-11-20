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

    // AJEITAR DESPUES
    matchStart(match);

    declareMenuButtons(game.menuButtons);
    declareHistoryButtons(game.historyButtons);
    game.historyPage = 0;
    game.historySortByName = false;

    game.state = MENU;
    game.quit = false;
}

void processMenuButClick(Game& game, Button& button){
    if      (strcmp(button.text, "PLAY") == 0)        game.state = PLAYING;
    else if (strcmp(button.text, "HOW TO PLAY") == 0) game.state = HOW_TO_PLAY;
    else if (strcmp(button.text, "HISTORY") == 0)     { game.state = HISTORY; game.historyPage = 0; }
    else if (strcmp(button.text, "SETTINGS") == 0)    game.state = SETTINGS;
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

        case SETTINGS:
            // settingsProcess();
            // drawSettings();
        break;

        case PLAYING:
            // matchProcess(game.current_match, game.current_match.spriteMatch[SPR_BACKGROUND], mouse);
            ambientProcess(game, mouse); //Mostra os botoes e desenha o fundo de acordo com o ambiente
        break;

    }
}




void ambientProcess(Game& game, Vector2 mouse){

    Match &match = game.current_match;

    if(sceneChanged(match.screen, match.prevScreen))
        correctCamera(match);
    match.prevScreen = match.screen;
    // printf("%d\n", match.player.selectedSlot);

    if (match.screen == KITCHEN || match.screen == FRIDGE)
        match.screen = (match.player.object.pos.x > 4800) ? FRIDGE : KITCHEN;

    int selectedInvSlot = changeInvSlot();
    if(selectedInvSlot != -1 && selectedInvSlot < INVENTORY_SLOTS)
        match.player.selectedSlot = selectedInvSlot;
    printf("%d ", match.player.selectedSlot + 1);
    printf("%d ", match.player.inventory[match.player.selectedSlot].size);
    printf("%d ", match.player.inventory[match.player.selectedSlot].capacity);
    printf("%d\n", match.player.inventory[match.player.selectedSlot].type);


    // 1. update
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
        default: break;
    }

    // 3. click
    switch(match.screen){
        case KITCHEN: { //The brackets garantee that the variable nearest only exists in the brackets and can't be used elsewhere in the switch so that we don't have de problem of an unnitialized veriable being used
            int nearest = nearestButtonIndex(match.player.object.pos.x, match.buttonsVec[match.screen]);
            if (keyUpClicked() && nearest != -1)
                processButClick(match, match.buttonsVec[match.screen].buttons[nearest]);
        } break;
        case PREPARE:
        case OVEN:
        case BOARD:
            if(keyDownClicked()) match.screen = KITCHEN;
        case FRIDGE:
            if(butUnderMouseInd != -1){
                Button& but = match.buttonsVec[match.screen].buttons[butUnderMouseInd];
                if (mouseKeyLeftClicked())
                    processButClick(match, but);
            }
        break;
        default: break;
    }

    cookAll(match.buttonsVec);
    processCostumers(match.costumer_line, match.costumer_counter, game.avl_orders, game.hashtable_orders);
}

void gameOver(Game& game){
    // unloadSpritesheet(game.spritesMenu);
    unloadSpritesheet(game.current_match.spriteMatch);
}
