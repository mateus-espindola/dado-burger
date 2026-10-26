#ifndef GAME_HPP
#define GAME_HPP

#include "data_structures.hpp"
#include "constants.hpp"
#include "tads.hpp"


/* ============================ */
/*      STRUCTS AND ENUMS       */
/* ============================ */

struct Sprite {
    Texture2D texture;
    int width, height;
};

struct PlayerInfo{
    char nome[50];
    int score;
};

struct Player {
    PlayerInfo info;
    Stack<Ingredient> inventory;
    Vector2 pos;
};

enum ButtonType {
    BUTTON_MENU,
    BUTTON_OVEN,
    BUTTON_BOARD,
    BUTTON_PREPARE,
    BUTTON_FRIDGE,
    BUTTON_TRASH,
    BUTTON_BELL,
};

struct Button {
    ButtonType type;
    Rectangle shape;
};

struct Slot {
    Button button;
    Stack<Ingredient> stack;
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
    List<Sprite> spritesheet;
};

/* ============================== */
/*      FUNCTION PROTOTYPES       */
/* ============================== */

void gameStart(Game& game);
void gameProcess(Game& game);
void gameOver(Game& game);

void loadSpritesheet(List<Sprite>& spritesheet);

// void menuProcess();
// void tutorialProcess();
// void historyProcess();
// void settingsProcess();
void matchProcess(Match& match);

void matchStart(Match& match);
void cameraProcess(Camera2D& camera, Player& player);
void playerProcess(Player& player);


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
