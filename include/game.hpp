#ifndef GAME_HPP
#define GAME_HPP

#include "data_structures.hpp"
#include "constants.hpp"

/* ============================ */
/*      STRUCTS AND ENUMS       */
/* ============================ */

struct PlayerInfo{
    char nome[50];
    int score;
    //Stack inventory[3];
    //Stack inventory;
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

/* ============================== */
/*      FUNCTION PROTOTYPES       */
/* ============================== */

void gameStart(Game& game);
void gameProcess(Game& game);
void gameOver(Game& game);

// void menuProcess();
// void tutorialProcess();
// void historyProcess();
// void settingsProcess();
// void matchProcess();

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
