#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "raylib.h"
#include "../include/constants.hpp"
#include "../include/data_structures.hpp"


void gameStart(Game& game);
void gameProcess(Game& game);
void gameDraw(Game& game);
void gameOver(Game& game);

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

#define BALCON_SIZE 3;

struct{

    char nome[50];
    int score;

} Player;

struct {
    
    int patience;
    Recipe order;
    Costumer_type type;

} Costumer;

enum {

    CHILL_GUY
    NORMAL
    VEGAN
    TONY

} Costumer_type;


enum {

    MENU
    HOW_TO_PLAY
    HISTORY
    SETTINGS
    PLAYING

} GameState;

enum {

    COUNTER
    KITCHEN
    PREPARE
    PAUSED
    DEFEAT
    VICTORY

} MatchState;

struct{

    bool quit;
    Match current_match;
    GameState gameState;

} Game;

struct {

    MatchState matchState;
    Costumer_queue fila;
    Clientes atender[BALCON_SIZE];
    int turn;
    //Hamburguers montando
    //Coisas do fogao
    //Coisas da tabua

} Match;


enum {

    LETTUCE = 'a'
    BACON = 'b'
    ONION = 'c'
    KETCHUP = 'k'
    MUSTARD = 'm'
    MEAT = 'n'
    FRIED_EGG = 'o'
    PICKLES = 'p'
    CHEDDAR = 'q'
    SWISS_CHEESE = 's'
    TOMATO = 't'
    UPPER_BREAD = 'z'

} IngredientType;


// 0 0
// 0 1
// 1 0
// 1 1



struct{
    IngredientType type;
    int tempo_perecivel; // turnos ate estragar. -1 se nao estraga
    int 

} Ingredient;



#endif
