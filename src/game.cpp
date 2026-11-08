#include <cstdio>
#include <cstring>

#include "../include/game.hpp"
#include "../include/graphics.hpp"
#include "../include/inputs.hpp"

#include "raylib.h"

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
            matchProcess(game.current_match, game.current_match.spriteMatch[SPR_BACKGROUND], mouse);
            ambientProcess(game, mouse); //Mostra os botoes e desenha o fundo de acordo com o ambiente
        break;

    }
}




void ambientProcess(Game& game, Vector2 mouse){

    Match &match = game.current_match;   // Referencia, nao copia

    printf("%d\n", game.current_match.screen);

    if (match.screen == KITCHEN || match.screen == FRIDGE)
        //Condição  ?   Se verdadeiro   :   Se falso
        match.screen = (match.player.object.pos.x > 4800) ? FRIDGE : KITCHEN;

    int butUnderMouseInd = findButtonUnderMouse(mouse, match.buttonsVec[match.screen], match.camera);

    switch(match.screen){
        case KITCHEN:
            drawKitchen(match, butUnderMouseInd);
            printf("%d %d\n", match.screen, butUnderMouseInd);
            if(mouseKeyLeftClicked() && butUnderMouseInd != -1){
                processButClick(match.screen, match.buttonsVec[match.screen], butUnderMouseInd);
                // for(int i = 0; i < 100; i++)
                //     printf("Entrou");
            }
        break;

        case FRIDGE:
            drawKitchen(match, butUnderMouseInd);
            if(mouseKeyLeftClicked() && butUnderMouseInd != -1)
                processButClick(match.screen, match.buttonsVec[match.screen], butUnderMouseInd);
        break;

        case OVEN:
            drawPrepare(match, butUnderMouseInd);
        break;

        case BOARD:
            drawPrepare(match, butUnderMouseInd);
        break;

        case PREPARE:
            drawPrepare(match, butUnderMouseInd);
            printf("%d %d\n", match.screen, butUnderMouseInd);

        break;

        case PAUSED:

        break;

        case DEFEAT:

        break;

        case VICTORY:

        break;
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