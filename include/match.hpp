#ifndef MATCH_HPP
#define MATCH_HPP

#include "raylib.h"

// #include "constants.hpp" //Usa mas o include nao e necessario. O inclide das constantes vem de player.hpp
#include "tads.hpp"
#include "food.hpp"
#include "sprites.hpp"
#include "buttons.hpp"
#include "player.hpp"




/* ============================ */
/*            MATCH             */
/* ============================ */

struct Items{

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
    // int turn;
    Items items;

};




/* ============================ */
/*  MATCH FUNCTIONS PROTOTYPES  */
/* ============================ */

void matchStart(Match& match);

// void matchProcess(Match& match);
void matchProcess(Match& match, Sprite background);
// void playerProcess(Player& player); Transferido para player.hpp



#endif
