#ifndef MATCH_HPP
#define MATCH_HPP

#include "constants.hpp"
#include "player.hpp"

#include "raylib.h"




/* ============================ */
/*            MATCH             */
/* ============================ */

enum MatchState{

    KITCHEN,
    OVEN,
    BOARD,
    PREPARE,
    PAUSED,
    DEFEAT,
    VICTORY,
    STATE_QUANTITY

};

struct Match{
    MatchState state;
    Button* buttons[STATE_QUANTITY];
    Camera2D camera;
    Player player;
    Queue<Costumer> costumer_line;
    Costumer costumer_counter[COUNTER_SIZE];
    int turn;
    //Hamburguers montando
    Stack<Ingredient> balcony[PREPARING_SPACE];
    //Coisas do fogao
    Stack<Ingredient> cooking_plate[PLATE_SIZE]; //Essa aqui é pra hamburguer
    Stack<Ingredient> pans[PAN_NUMBER]; //Essa aqui é pra ovo
    //Coisas da tabua
    //Tres pilhas para 3 ingredientes diferentes
    //VAMOS SEPARAR OS PRONTOS DA TABUA COM OS PRONTOS DO FOGAO OU DEIXA
    //TUDO NO MESMO VETOR DE PILHAS?
    Stack<Ingredient> post_prepare_space[STOARGE_SIZE];

};




/* ============================ */
/*  MATCH FUNCTIONS PROTOTYPES  */
/* ============================ */

void matchStart(Match& match);

void matchProcess(Match& match);
void playerProcess(Player& player);



#endif
