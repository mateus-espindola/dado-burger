#ifndef MATCH_HPP
#define MATCH_HPP

#include "raylib.h"

// #include "constants.hpp" //Usa mas o include nao e necessario. O inclide das constantes vem de player.hpp
#include "tads.hpp"
#include "food.hpp"
#include "sprites.hpp"
#include "buttons.hpp"
#include "player.hpp"
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
    MatchScreen prevScreen; //Used to detect screen changes during the matc
    ButtonVec buttonsVec[STATE_QUANTITY];
    Camera2D camera;
    Player player;
    Queue<Costumer> costumer_line;
    Costumer costumer_counter[COUNTER_SIZE];
    // int turn;
    Items items;
    Sprite spriteMatch[QUANTITY_OF_SPRITES];

};




/* ============================ */
/*  MATCH FUNCTIONS PROTOTYPES  */
/* ============================ */

void matchStart(Match& match);

// void matchProcess(Match& match);
// void matchProcess(Match& match, Sprite background, Vector2 mouse);
// void playerProcess(Player& player); Transferido para player.hpp



#endif
