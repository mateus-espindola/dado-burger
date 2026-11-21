#pragma once

#include "game.hpp"

// void gameDraw(Game& game);
void drawMenu(const ButtonVec& menuButtons, int butUnderMouseInd);
void drawHistory(const ContiguousList<PlayerInfo>& historico, int page, const ButtonVec& historyButtons, int butUnderMouseInd);
// void tutorialDraw();
// void historyDraw();
// void settingsDraw();
// void matchDraw(Match& match);

Vector2 getSpritePos(Object& object);


//MOVIDOS PARA SPRITES.HPP
// void spriteDraw(Sprite& sprite, Vector2 pos, float scale, Color tint);
// void warDetirps(Sprite& sprite, Vector2 pos, float scale, Color tint);

void hitboxDraw(const Object&);

//COLOCAR CONST DEPOIS
void playerDraw(Player&);

// void drawNearestBut(const Player &player, Button **buttons);
int drawNearestBut(const Player& player, const ButtonVec& screenButtons);

void drawButtons(const ButtonVec& screenButtons, int butUnderMouseInd, MatchScreen screenId);

void drawKitchen(Match& match, int butUnderMouseInd);

void drawButGlow(Rectangle r, Color cor, int camadas, float alpha);

void drawBoard(Match match, int butUnderMouseInd);

void drawStove(Match& match, int butUnderMouseInd);

void drawPrepare(Match& match, int butUnderMouseInd);

void drawInventory(const Player &player);

void drawIngredient(Vector2 center, float radius, const Ingredient& ing);

void drawStack(const Stack& stack, Vector2 basePos, float radius = 20.0f, float offset = 6.0f);

void drawHeap(const Heap<Ingredient>& heap, Vector2 basePos, float radius = 20.0f, float offset = 6.0f);

void drawStackButtons(const ButtonVec& screenButtons);

void drawCtrlHintFor(Rectangle button, int screen);

void drawCostumers(Queue<Costumer>& queue, Costumer counter[], Vector2 mouseWorld);
