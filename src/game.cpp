#include <cstdio>
#include <cstring>
#include <string>

#include "../include/game.hpp"
#include "../include/graphics.hpp"
#include "../include/inputs.hpp"
#include "../include/camera.hpp"
#include "../include/world.hpp"

#include "raylib.h"

void readFiles(Game& game, FILE* fp, FILE* fh) {
    if (fp == nullptr || fh == nullptr) {
        std::cout << "There was an error while trying to read the archive." << std::endl;
    }

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

}

void gameStart(Game& game){


    Match &match = game.current_match;
    // loadSpritesheet(game.spritesMenu);
    loadSpritesheet(match.spriteMatch);

    match.player.object.sprite = match.spriteMatch[SPR_PLAYER];
    match.player.object.radius = PLAYER_HITBOX_RADIUS;

    // AJEITAR DESPUES
    matchStart(match);

    game.state = PLAYING;
    game.quit = false;
}

void gameProcess(Game& game){
    if (IsKeyPressed(KEY_ESCAPE)) game.quit = true;

    Vector2 mouse = findMousePos();

    switch(game.state) {

        case MENU:
            // menuProcess();
            // drawMenu();
        break;

        case HOW_TO_PLAY:
            // tutorialProcess();
            // drawHowToPlay();
        break;

        case HISTORY:
            // historyProcess();
            // drawHistory();
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

    cookAll(match.buttonsVec, COOK_SPEED);

}

void gameOver(Game& game){
    // unloadSpritesheet(game.spritesMenu);
    unloadSpritesheet(game.current_match.spriteMatch);
}
