#pragma once

#include "raylib.h"

#include "tads.hpp"
#include "food.hpp"
#include "sprites.hpp"
#include "buttons.hpp"
#include "player.hpp"
#include "costumer.hpp"
#include "match_enums.hpp"




/* ============================ */
/*            MATCH             */
/* ============================ */

struct Items{

    //Hamburguers montando
    Stack balcony[PREPARING_SPACE];
    //Coisas do fogao
    Stack cooking_plate[PLATE_SIZE]; //Essa aqui é pra hamburguer
    Stack pans[PAN_NUMBER]; //Essa aqui é pra ovo
    //Coisas da tabua
    //Tres pilhas para 3 ingredientes diferentes
    //VAMOS SEPARAR OS PRONTOS DA TABUA COM OS PRONTOS DO FOGAO OU DEIXA
    //TUDO NO MESMO VETOR DE PILHAS?
    Stack post_prepare_space[STOARGE_SIZE];

};

struct Match{
    MatchScreen screen;
    MatchScreen prevScreen; //Used to detect screen changes during the match
    MatchScreen screenBeforePause; //Pra onde "RESUME MATCH" volta
    ButtonVec buttonsVec[STATE_QUANTITY];
    Camera2D camera;
    Player player;

    int profitGoal;

    char nameInput[HISTORY_NAME_BUFFER]; // nome sendo digitado na tela de VICTORY
    int nameInputLen;

    Queue<Costumer> costumer_line;
    Costumer costumer_counter[COUNTER_SIZE];

    Items items;
    Sprite spriteMatch[QUANTITY_OF_SPRITES];

};




/* ============================ */
/*  MATCH FUNCTIONS PROTOTYPES  */
/* ============================ */

void matchStart(Match& match);
void matchEnd(Match& match);
void winMatch(Match& match);
void loseMatch(Match& match);

void setIngredients(ButtonVec screens[], int screenCount);
