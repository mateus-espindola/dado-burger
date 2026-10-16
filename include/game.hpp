#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "raylib.h"
#include "../include/constants.hpp"
#include "../include/data_structures.hpp"

/* ============================ */
/*      STRUCTS AND ENUMS       */
/* ============================ */

struct PlayerInfo{
    char nome[50];
    int score;
};

enum CostumerType{

    CHILL_GUY,
    NORMAL,
    VEGAN,
    TONY

};

struct Costumer{
    int patience;
    Recipe order;
    CostumerType type;
};

enum MatchState{

    /* COUNTER,
    KITCHEN,
    PREPARE, */
    PAUSED,
    DEFEAT,
    VICTORY

};

struct Match{
    MatchState state;
    Costumer_queue costumer_line;
    Costumer costumer_counter[COUNTER_SIZE];
    int turn;
    //Hamburguers montando
    //Coisas do fogao
    //Coisas da tabua
};

enum GameState{

    MENU,
    HOW_TO_PLAY,
    HISTORY,
    SETTINGS,
    PLAYING

};

struct Game{
    bool quit;
    Match current_match;
    GameState state;
};

enum IngredientType{

    LETTUCE = 'a',
    BACON = 'b',
    ONION = 'c',
    KETCHUP = 'k',
    MUSTARD = 'm',
    MEAT = 'n',
    FRIED_EGG = 'o',
    PICKLES = 'p',
    CHEDDAR = 'q',
    SWISS_CHEESE = 's',
    TOMATO = 't',
    UPPER_BREAD = 'z'

};

struct Ingredient{
    IngredientType type;
    int tempo_perecivel; // turnos ate estragar. -1 se nao estraga
};

/* ============================== */
/*      FUNCTION PROTOTYPES       */
/* ============================== */

void gameStart(Game& game);
void gameProcess(Game& game);
void gameOver(Game& game);

void menuProcess();
void tutorialProcess();
void historyProcess();
void settingsProcess();
void matchProcess();

#endif

/* RASCUNHOS */

// 0 0
// 0 1
// 1 0
// 1 1

//Struct jogador

//Struct cliente

//Struct do jogo (gamestate)

//Struct ingredientes com as caracteristicas dos ingredientes (pereciveis, necessitam de preparo...)

//Biblioteca de dados

//Fila com clientes
//Controlar os tempos de preparo
//Mais de uma tela de visao



//Botao de passar turno
//Numero de acoes por turno
//Acabar acoes = passar turno automaticamente

//Botao de troca de cenario
//No botao balcao aparace excalamacao se tiver algum cliente a um turno de te mandar tomar no cu

//Tres clientes no balcao por vez
