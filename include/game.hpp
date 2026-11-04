
#include "match.hpp"
#include "raylib.h"


/* ============================ */
/*            SPRITES           */
/* ============================ */

enum SpriteType {
    SPR_BACKGROUND,
    SPR_PLAYER,
    QUANTITY_OF_SPRITES
};

struct Sprite {
    Texture2D texture;
    int width, height;
};

<<<<<<< HEAD

=======
struct Object {
    Sprite sprite;
    Vector2 pos;
    float radius;
};

enum Direction {
    DIR_LEFT,
    DIR_RIGHT
};

struct PlayerInfo{
    char nome[50];
    int score;
};

struct Player {
    Object object;
    PlayerInfo info;
    Stack<Ingredient> inventory;
    Direction direction;
};
>>>>>>> f81ab36a65a1122e1733b2804398d4964509821a


/* ============================ */
/*             GAME             */
/* ============================ */

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
    Sprite sprites[QUANTITY_OF_SPRITES];
};

/* ============================== */
/*      FUNCTION PROTOTYPES       */
/* ============================== */

void gameStart(Game& game);
void gameProcess(Game& game);
void gameOver(Game& game);

void loadSpritesheet(Sprite sprites[]);
void unloadSpritesheet(Sprite sprites[]);

// void menuProcess();
// void tutorialProcess();
// void historyProcess();
// void settingsProcess();
<<<<<<< HEAD
=======
void matchProcess(Match& match, Sprite background);

void matchStart(Match& match);

void cameraProcess(Camera2D& camera, Player& player, Sprite background);
void playerProcess(Player& player, Sprite background);
>>>>>>> f81ab36a65a1122e1733b2804398d4964509821a





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
