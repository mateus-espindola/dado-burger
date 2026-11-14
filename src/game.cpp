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

    // for (int i = 0; i < INVENTORY_SLOTS; i++) {
    // printf("Slot %d: count=%d, top=%p\n",
    //        i,
    //        match.player.inventory[i].count,
    //        (void*)match.player.inventory[i].items.top);
    // }

    // if (match.player.selectedSlot < 0 ||
    // match.player.selectedSlot >= INVENTORY_SLOTS) {
    // printf("SELECTED SLOT INVALID: %d\n",
    //        match.player.selectedSlot);
    // return;
    // }

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
            if (mouseKeyLeftClicked() && butUnderMouseInd != -1)
                processButClick(match, match.buttonsVec[match.screen].buttons[butUnderMouseInd]);
        break;
        default: break;
    }

}

void gameOver(Game& game){
    // unloadSpritesheet(game.spritesMenu);
    unloadSpritesheet(game.current_match.spriteMatch);
}


//TRANSFERIDA PARA CAMERA.CPP
// void cameraProcess(Camera2D& camera, Player& player, Sprite background) {
//     Vector2 targetPos = { player.object.pos.x, player.object.pos.y};

//     camera.target.x += (targetPos.x - camera.target.x) * CAMERA_INTERPOOLATION;

//     if (camera.target.x < camera.offset.x) {
//         camera.target.x = camera.offset.x;
//     }
//     if (camera.target.x > background.width * GAME_SCALE - camera.offset.x) {
//         camera.target.x = background.width * GAME_SCALE - camera.offset.x;
//     }
// }


//TRANSFERIDA PARA PLAYER.CPP
// void playerProcess(Player& player, Sprite background) {
//     int playerSpeed;
//     if (IsKeyDown(KEY_LEFT_SHIFT)) {
//         playerSpeed = PLAYER_SPEED * 2;
//     } else {
//         playerSpeed = PLAYER_SPEED;
//     }

//     if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
//         player.direction = DIR_RIGHT;
//         player.object.pos.x += playerSpeed;
//     }
//     if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
//         player.direction = DIR_LEFT;
//         player.object.pos.x -= playerSpeed;
//     }

//     float minX = 0.0f + (player.object.sprite.width * GAME_SCALE) / 2;
//     float maxX = background.width * GAME_SCALE - (player.object.sprite.width * GAME_SCALE) / 2;

//     if (player.object.pos.x < minX) player.object.pos.x = minX;
//     if (player.object.pos.x > maxX) player.object.pos.x = maxX;
// }
